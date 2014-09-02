// =====
// BEGIN: mk_test_ll.c
// ====
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#include "./include/common.h"
#include "./include/nstring.h"
#include "./include/runtime.h"
#include "./include/rcu.h"
#include "./include/mem.h"
#include "./include/list.h"
#include "./include/skiplist.h"

#define USE_SYSTEM_MALLOC
#define ENABLE_TRACE


static int num_threads_;
static volatile int start_, stop_, load_;
//static map_t *map_;
static  list_t *ll_;
static int get_range_, put_range_;
static size_t num_keys_;
static double load_time_;
static int duration_;

#define OP_SELECT_RANGE (1ULL << 20)

#define NUM_THREADS 4

#define SIZE 1024


void *thread_func(void *tid) {
    unsigned m = 0;

    unsigned w = m * 11 + (uint64_t)tid;
    map_key_t key = (w * 7) % SIZE;

    assert(key != 0);
    ll_cas(ll_, key, CAS_EXPECT_WHATEVER, key);
    return NULL;
}

int main (int argc, char **argv) {
    char* program_name = argv[0];
    ll_ = ll_alloc(NULL);

    pthread_t threads[NUM_THREADS];

    int i;
    for (i = 0; i < NUM_THREADS; ++i) {
      pthread_create(&threads[i], NULL, thread_func, (void *) (i + 1));
    }

    for (i = 0; i < NUM_THREADS; ++i) {
      pthread_join(threads[i], NULL);
    }

    ll_print(ll_, FALSE);
    ll_free(ll_);

    return 0;
}

// ====
// ====
// END: mk_test_ll.c
// ====

// ====
// BEGIN: runtime/runtime.c
// ====
/*
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 */
#define _POSIX_C_SOURCE 1 // for rand_r()
#include <stdlib.h>
#include <pthread.h>
#include "./include/common.h"
#include "./include/runtime.h"
#include "./runtime/rlocal.h"
#include "./include/mem.h"
#include "./include/tls.h"

DECLARE_THREAD_LOCAL(tid_, int);
DECLARE_THREAD_LOCAL(rx_, uint32_t);
DECLARE_THREAD_LOCAL(ry_, uint32_t);
DECLARE_THREAD_LOCAL(rz_, uint32_t);
DECLARE_THREAD_LOCAL(rc_, uint32_t);

typedef struct thread_info {
    int thread_id;
    void *(*start_routine)(void *);
    void *restrict arg;
} thread_info_t;

__attribute__ ((constructor)) void nbd_init (void) {
    INIT_THREAD_LOCAL(r);
    INIT_THREAD_LOCAL(tid_);
    SET_THREAD_LOCAL(tid_, 0);
    mem_init();
    lwt_thread_init(0);
    rcu_thread_init(0);
    srand((uint32_t)rdtsc());
}

#if 0
static void *worker (void *arg) {
    thread_info_t *ti = (thread_info_t *)arg;
    SET_THREAD_LOCAL(tid_, ti->thread_id);
    LOCALIZE_THREAD_LOCAL(tid_, int);

    SET_THREAD_LOCAL(rx_, rand());
    SET_THREAD_LOCAL(ry_, rand());
    SET_THREAD_LOCAL(rz_, rand());
    SET_THREAD_LOCAL(rc_, rand());

    lwt_thread_init(ti->thread_id);
    rcu_thread_init(ti->thread_id);

    void *ret = ti->start_routine(ti->arg);
    nbd_free(ti);
    return ret;
}

int nbd_thread_create (pthread_t *restrict thread, int thread_id, void *(*start_routine)(void *), void *restrict arg) {
    thread_info_t *ti = (thread_info_t *)nbd_malloc(sizeof(thread_info_t));
    ti->thread_id = thread_id;
    ti->start_routine = start_routine;
    ti->arg = arg;
    return pthread_create(thread, NULL, worker, ti);
}
#endif

// George Marsaglia's KISS generator
uint64_t nbd_rand (void) {
    LOCALIZE_THREAD_LOCAL(rx_, unsigned);
    LOCALIZE_THREAD_LOCAL(ry_, unsigned);
    LOCALIZE_THREAD_LOCAL(rz_, unsigned);
    LOCALIZE_THREAD_LOCAL(rc_, unsigned);

    uint32_t rx = 69069 * rx_ + 12345;
    uint32_t ry = ry_;
    uint32_t rz = rz_;
    ry ^= (ry << 13);
    ry ^= (ry >> 17);
    ry ^= (ry <<  5);
    uint64_t t = rz * 698769069LL + rc_;
    uint64_t r = rx + ry + (rz = t);

    SET_THREAD_LOCAL(rx_, rx);
    SET_THREAD_LOCAL(ry_, ry);
    SET_THREAD_LOCAL(rz_, rz);
    SET_THREAD_LOCAL(rc_, t >> 32);

    return r;
}

// Fairly fast random numbers
uint64_t nbd_rand_seed (int i) {
    return rdtsc() + -715159705 + i * 129;
}

int nbd_next_rand (uint64_t *r) {
    *r = (*r * 0x5DEECE66DLL + 0xBLL) & MASK(48);
    return (*r >> 17) & 0x7FFFFFFF;
}
// ====
// END: runtime/runtime.c
// ====

// ====
// BEGIN: runtime/rcu.c
// ====
/*
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 *
 * safe memory reclamation using a simple technique from rcu
 *
 * WARNING: not robust enough for real-world use
 */
#include <string.h>
#include "./include/common.h"
#include "./runtime/rlocal.h"
#include "./include/lwt.h"
#include "./include/mem.h"
#include "./include/tls.h"
#include "./include/rcu.h"

#define RCU_POST_THRESHOLD 10
#define RCU_QUEUE_SCALE 20

typedef struct fifo {
    uint32_t head;
    uint32_t tail;
    uint32_t scale;
    void *x[0];
} fifo_t;

#define MOD_SCALE(x, b) ((x) & MASK(b))
static uint64_t rcu_[MAX_NUM_THREADS][MAX_NUM_THREADS] = {};
static uint64_t rcu_last_posted_[MAX_NUM_THREADS][MAX_NUM_THREADS] = {};
static fifo_t *pending_[MAX_NUM_THREADS] = {};
static int num_threads_ = 0;

static fifo_t *fifo_alloc(int scale) {
    fifo_t *q = (fifo_t *)nbd_malloc(sizeof(fifo_t) + (1ULL << scale) * sizeof(void *));
    memset(q, 0, sizeof(fifo_t));
    q->scale = scale;
    q->head = 0;
    q->tail = 0;
    return q;
}

void rcu_thread_init (int id) {
    //assert(id < MAX_NUM_THREADS);
    if (pending_[id] == NULL) {
        pending_[id] = fifo_alloc(RCU_QUEUE_SCALE);
        (void)SYNC_ADD(&num_threads_, 1);
    }
}

void rcu_update (void) {
    LOCALIZE_THREAD_LOCAL(tid_, int);
    //assert(tid_ < num_threads_);
    int next_thread_id = (tid_ + 1) % num_threads_;
    TRACE("r1", "rcu_update: updating thread %llu", next_thread_id, 0);
    int i;
    for (i = 0; i < num_threads_; ++i) {
        if (i == tid_)
            continue;

        // No need to post an update if the value hasn't changed
        if (rcu_[tid_][i] == rcu_last_posted_[tid_][i])
            continue;

        uint64_t x = rcu_[tid_][i];
        rcu_[next_thread_id][i] = rcu_last_posted_[tid_][i] = x;
        TRACE("r2", "rcu_update: posted updated value (%llu) for thread %llu", x, i);
    }

    // free
    fifo_t *q = pending_[tid_];
    while (q->tail != rcu_[tid_][tid_]) {
        uint32_t i = MOD_SCALE(q->tail, q->scale);
        TRACE("r0", "rcu_update: freeing %p from queue at position %llu", q->x[i], q->tail);
        nbd_free(q->x[i]);
        q->tail++;
    }
}

void rcu_defer_free (void *x) {
    //assert(x);
    LOCALIZE_THREAD_LOCAL(tid_, int);
    fifo_t *q = pending_[tid_];
    //assert(MOD_SCALE(q->head + 1, q->scale) != MOD_SCALE(q->tail, q->scale));
    uint32_t i = MOD_SCALE(q->head, q->scale);
    q->x[i] = x;
    TRACE("r0", "rcu_defer_free: put %p on queue at position %llu", x, q->head);
    q->head++;

    if (pending_[tid_]->head - rcu_last_posted_[tid_][tid_] >= RCU_POST_THRESHOLD) {
        TRACE("r0", "rcu_defer_free: posting %llu", pending_[tid_]->head, 0);
        int next_thread_id = (tid_ + 1) % num_threads_;
        rcu_[next_thread_id][tid_] = rcu_last_posted_[tid_][tid_] = pending_[tid_]->head;
    }
}
// ====
// END: runtime/rcu.c
// ====

// ====
// BEGIN: runtime/lwt.c
// ====
/* 
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 *
 * lightweight tracing 
 */
#include <stdio.h>
#include "./include/common.h"
#include "./runtime/rlocal.h"
#include "./include/lwt.h"
#include "./include/mem.h"

#define LWT_BUFFER_SCALE 20
#define LWT_BUFFER_SIZE (1ULL << LWT_BUFFER_SCALE)
#define LWT_BUFFER_MASK (LWT_BUFFER_SIZE - 1)

volatile int halt_ = 0;

typedef struct lwt_record {
    uint64_t timestamp;
    uint64_t format;
    size_t value1;
    size_t value2;
} lwt_record_t;

typedef struct lwt_buffer {
    uint32_t head;
    lwt_record_t x[0];
} lwt_buffer_t;

lwt_buffer_t *lwt_buf_[MAX_NUM_THREADS] = {};
char flag_state_[256] = {};
static const char *flags_ = "";

void lwt_thread_init (int thread_id)
{
    //assert(thread_id < MAX_NUM_THREADS);
    if (lwt_buf_[thread_id] == NULL) {
        lwt_buf_[thread_id] = (lwt_buffer_t *)nbd_malloc(sizeof(lwt_buffer_t) + sizeof(lwt_record_t) * LWT_BUFFER_SIZE);
        memset(lwt_buf_[thread_id], 0, sizeof(lwt_buffer_t));
    }
}

void lwt_set_trace_level (const char *flags)
{
    //assert(strlen(flags) % 2 == 0); // a well formed <flags> should be an even number of characters long
    flags_ = flags;
    memset(flag_state_, 0, sizeof(flag_state_));
    for (int i = 0; flags[i]; i+=2) {
        flag_state_[(unsigned)flags[i]] = flags[i+1];
    }
}

static void dump_record (FILE *file, int thread_id, lwt_record_t *r, uint64_t offset)
{
    // print the record if its trace category is enabled at a high enough level
    int flag  =  r->format >> 56;
    int level = (r->format >> 48) & 0xFF;
    if (flag_state_[(unsigned)flag] >= level) {
        char s[3] = {flag, level, '\0'};
        fprintf(file, "%09llu %d %s ", ((uint64_t)r->timestamp - offset) >> 5, thread_id, s);
        const char *format = (const char *)(size_t)(r->format & MASK(48)); // strip out the embedded flags
        fprintf(file, format, r->value1, r->value2);
        fprintf(file, "\n");
    }
}

static void dump_buffer (FILE *file, int thread_id, uint64_t offset)
{
    lwt_buffer_t *tb = lwt_buf_[thread_id]; 
    //assert(tb);
    if (tb->head > LWT_BUFFER_SIZE) {
        for (int i = tb->head & LWT_BUFFER_MASK; i < LWT_BUFFER_SIZE; ++i) {
            dump_record(file, thread_id, tb->x + i, offset);
        }
    }

    for (int i = 0; i < (tb->head & LWT_BUFFER_MASK); ++i) {
        dump_record(file, thread_id, tb->x + i, offset);
    }
}

void lwt_halt (void) {
    halt_ = 1;
}

void lwt_dump (const char *file_name)
{
    halt_ = 1;
    uint64_t offset = (uint64_t)-1;

    for (int i = 0; i < MAX_NUM_THREADS; ++i) {
        if (lwt_buf_[i] != NULL && lwt_buf_[i]->head != 0) {
            uint64_t x = lwt_buf_[i]->x[0].timestamp;
            if (x < offset) {
                offset = x;
            }
            if (lwt_buf_[i]->head > LWT_BUFFER_SIZE)
            {
                x = lwt_buf_[i]->x[lwt_buf_[i]->head & LWT_BUFFER_MASK].timestamp;
                if (x < offset) {
                    offset = x;
                }
            }
        }
    }

    if (offset != (uint64_t)-1) {
        FILE *file = fopen(file_name, "w");
        //assert(file);
        for (int i = 0; i < MAX_NUM_THREADS; ++i) {
            if (lwt_buf_[i] != NULL) {
                dump_buffer(file, i, offset);
            }
        }
        fflush(file);
        fclose(file);
    }
}

void lwt_trace_i (uint64_t format, size_t value1, size_t value2) {
    while (halt_) {}
    LOCALIZE_THREAD_LOCAL(tid_, int);
    lwt_buffer_t *tb = lwt_buf_[tid_];
    if (tb != NULL) {
        unsigned int u, l;
        //__asm__ __volatile__("rdtsc" : "=a" (l), "=d" (u)); 
        //u = rtdsc(u, l);
        u = 37;
        l = 33;
        uint64_t timestamp = ((uint64_t)u << 32) | l; 
        lwt_record_t temp = { timestamp, format, value1, value2 };

        tb->x[tb->head++ & LWT_BUFFER_MASK] = temp;
    }
}
// ====
// END: runtime/lwt.c
// ====

// ====
// BEGIN: runtime/mem.c
// ====
/* 
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 *
 * Extreamly fast multi-threaded malloc.
 */
#ifndef USE_SYSTEM_MALLOC
#define _BSD_SOURCE // so we get MAP_ANON on linux
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include "./include/common.h"
#include "./runtime/rlocal.h"
#include "./include/lwt.h"

#ifndef NBD32
#define MAX_SCALE        36 // allocate blocks up to 64GB (arbitrary, could be bigger)
#define MIN_SCALE         3 // smallest allocated block is 8 bytes
#define MAX_POINTER_BITS 48
#define PAGE_SCALE       21 // 2MB pages
#else
#define MAX_SCALE        31 
#define MIN_SCALE         2 // smallest allocated block is 4 bytes
#define MAX_POINTER_BITS 32
#define PAGE_SCALE       12 // 4KB pages
#endif
#define PAGE_SIZE        (1ULL << PAGE_SCALE)
#define HEADERS_SIZE     (((size_t)1ULL << (MAX_POINTER_BITS - PAGE_SCALE)) * sizeof(header_t))

typedef struct block {
    struct block *next;
} block_t;

// TODO: Break the page header into two parts. The first part is located in the header region. The 
//       second part is located on the page and is only used when there are free items.
typedef struct header {
#ifdef  RECYCLE_PAGES
    struct header *next;
    struct header *prev;
    block_t *free_list; // list of free blocks
    int num_in_use;
#endif//RECYCLE_PAGES
    uint8_t owner; // thread id of owner
    uint8_t scale; // log2 of the block size
} header_t;

#ifdef RECYCLE_PAGES
typedef struct size_class {
    header_t *active_page;
    header_t *oldest_partial;
    header_t *newest_partial;
} size_class_t;
#endif//RECYCLE_PAGES

typedef struct tl {
#ifndef RECYCLE_PAGES
    block_t *free_list[MAX_SCALE+1];
#else
    header_t *free_pages;
    size_class_t size_class[MAX_SCALE+1];
#endif//RECYCLE_PAGES
    block_t *blocks_from[MAX_NUM_THREADS];
    block_t *blocks_to[MAX_NUM_THREADS];
} __attribute__((aligned(CACHE_LINE_SIZE))) tl_t;

static header_t *headers_ = NULL;

static tl_t tl_[MAX_NUM_THREADS] = {};

static inline header_t *get_header (void *r) {
    //ASSERT(((size_t)r >> PAGE_SCALE) < HEADERS_SIZE);
    return headers_ + ((size_t)r >> PAGE_SCALE);
}

static void *get_new_region (int block_scale) {
    LOCALIZE_THREAD_LOCAL(tid_, int);
#ifdef RECYCLE_PAGES
    tl_t *tl = &tl_[tid_]; // thread-local data
    if (block_scale <= PAGE_SCALE && tl->free_pages != NULL) {
        void *region = tl->free_pages;
        tl->free_pages = tl->free_pages->next;
        get_header(region)->scale = block_scale;
        return region;
    }
#endif//RECYCLE_PAGES
    size_t region_size = (1ULL << block_scale);
    if (region_size < PAGE_SIZE) {
        region_size = PAGE_SIZE;
    }
    void *region = mmap(NULL, region_size, PROT_READ|PROT_WRITE, MAP_NORESERVE|MAP_ANON|MAP_PRIVATE, -1, 0);
    TRACE("m1", "get_new_region: mmapped new region %p (size %p)", region, region_size);
    if (region == (void *)-1) {
        perror("get_new_region: mmap");
        exit(-1);
    }
    if ((size_t)region & (region_size - 1)) {
        TRACE("m0", "get_new_region: region not aligned", 0, 0);
        munmap(region, region_size);
        region = mmap(NULL, region_size * 2, PROT_READ|PROT_WRITE, MAP_NORESERVE|MAP_ANON|MAP_PRIVATE, -1, 0);
        if (region == (void *)-1) {
            perror("get_new_region: mmap");
            exit(-1);
        }
        TRACE("m0", "get_new_region: mmapped new region %p (size %p)", region, region_size * 2);
        void *aligned = (void *)(((size_t)region + region_size) & ~(region_size - 1));
        size_t extra = (char *)aligned - (char *)region;
        if (extra) {
            munmap(region, extra);
            TRACE("m0", "get_new_region: unmapped extra memory %p (size %p)", region, extra);
        }
        extra = ((char *)region + region_size) - (char *)aligned;
        if (extra) {
            munmap((char *)aligned + region_size, extra);
            TRACE("m0", "get_new_region: unmapped extra memory %p (size %p)", (char *)aligned + region_size, extra);
        }
        region = aligned;
    }
    //assert(region);

    header_t *h = get_header(region);
    TRACE("m1", "get_new_region: header %p (%p)", h, h - headers_);
    //assert(h->scale == 0);
    h->scale = block_scale;
    h->owner = tid_;

    return region;
}

void mem_init (void) {
    //assert(headers_ == NULL);
    // Allocate space for the page headers. This could be a big chunk of memory on 64 bit systems,
    // but it just takes up virtual address space. Physical space used by the headers is still 
    // proportional to the amount of memory the user mallocs.
    headers_ = mmap(NULL, HEADERS_SIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
    TRACE("m1", "mem_init: header page %p", headers_, 0);

    // initialize spsc queues
    for (int i = 0; i < MAX_NUM_THREADS; ++i) {
        for (int j = 0; j < MAX_NUM_THREADS; ++j) {
            if (i != j) {
                tl_[i].blocks_to[j] = (block_t *)&(tl_[j].blocks_from[i]);
            }
        }
    }
}

void nbd_free (void *x) {
    TRACE("m1", "nbd_free: block %p page %p", x, (size_t)x & ~MASK(PAGE_SCALE));
    //ASSERT(x);
    LOCALIZE_THREAD_LOCAL(tid_, int);
    block_t  *b = (block_t *)x;
    header_t *h = get_header(x);
    int b_scale = h->scale;
    TRACE("m1", "nbd_free: header %p scale %llu", h, b_scale);
    //ASSERT(b_scale && b_scale <= MAX_SCALE);
#ifdef RECYCLE_PAGES
    if (b_scale > PAGE_SCALE) {
        int rc = munmap(x, 1ULL << b_scale);
        //ASSERT(rc == 0);
        rc = rc;
    }
#endif
#ifndef NDEBUG
    memset(b, 0xcd, (1ULL << b_scale)); // bear trap
#endif
    tl_t *tl = &tl_[tid_]; // thread-local data
    if (h->owner == tid_) {
        TRACE("m1", "nbd_free: private block, old free list head %p", tl->free_list[b_scale], 0);

#ifndef RECYCLE_PAGES
        b->next = tl->free_list[b_scale];
        tl->free_list[b_scale] = b;
#else //RECYCLE_PAGES
        b->next = h->free_list;
        h->free_list = b;
        h->num_in_use--;
        size_class_t *sc = &tl->size_class[b_scale];
        if (sc->active_page != h) {
            if (h->num_in_use == 0) {
                // remove <h> from the partial-page list
                if (h->next != NULL) { h->next->prev = h->prev; }
                if (h->prev != NULL) { h->prev->next = h->next; }
                // put <h> on the free-page list
                h->next = tl->free_pages;
                tl->free_pages = h;
            } else {
                // move <h> to the top of the partial-page list
                if (h->next != NULL) {
                    h->next->prev = h->prev;
                    if (h->prev != NULL) { h->prev->next = h->next; }
                    h->prev = sc->newest_partial;
                    h->next = NULL;
                    sc->newest_partial = h;
                }
            }
        }
#endif//RECYCLE_PAGES
    } else {
        // push <b> onto it's owner's queue
        int b_owner = h->owner;
        TRACE("m1", "nbd_free: owner %llu", b_owner, 0);
        
        // The assignment statements are volatile to prevent the compiler from reordering them.
        VOLATILE_DEREF(b).next = NULL; 
        VOLATILE_DEREF(tl->blocks_to[b_owner]).next = b;

        tl->blocks_to[b_owner] = b;
    }
}

static inline void process_incoming_blocks (tl_t *tl) {
    for (int p = 0; p < MAX_NUM_THREADS; ++p) {
        block_t *b = tl->blocks_from[p];
        if (EXPECT_FALSE(b == NULL)) continue; // the queue is completely empty

        // Leave the last block on the queue. Removing the last block on the queue would create a
        // race with the producer thread putting a new block on the queue.
        for (block_t *next = b->next; next != NULL; b = next, next = b->next) {
            // push <b> onto the appropriate free list
#ifndef RECYCLE_PAGES
            int b_scale = get_header(b)->scale;
            b->next = tl->free_list[b_scale];
            tl->free_list[b_scale] = b;
#else //RECYCLE_PAGES
            header_t *h = get_header(b);
            b->next = h->free_list;
            h->free_list = b;
#endif//RECYCLE_PAGES
        }
        tl->blocks_from[p] = b;
    }
}

static inline block_t *pop_free_list (tl_t *tl, int scale) {
#ifndef RECYCLE_PAGES
    block_t **free_list = &tl->free_list[scale];
#else //RECYCLE_PAGES
    size_class_t *sc = &tl->size_class[scale];
    if (EXPECT_FALSE(sc->active_page == NULL))
        return NULL;
    block_t **free_list = &sc->active_page->free_list;
#endif//RECYCLE_PAGES
    block_t *b = *free_list;
    if (EXPECT_FALSE(b == NULL))
        return NULL;
    //ASSERT(get_header(b)->scale == scale);
    *free_list = b->next;
    return b;
}

// Allocate a block of memory at least size <n>. Blocks are binned in powers-of-two. Round up <n> to
// the nearest power of two. 
//
// First check the current thread's free list for an available block. If there are no blocks on the
// free list, pull items off of the current thread's incoming block queues and push them onto the 
// free list. If we didn't get an appropriate size block off of the block queues then allocate a new
// page, break it up into blocks and push them onto the free list. 
void *nbd_malloc (size_t n) {
    // the scale is the log base 2 of <n>, rounded up
    int b_scale = (sizeof(void *) * __CHAR_BIT__) - __builtin_clzl((n) - 1);
    TRACE("m1", "nbd_malloc: size %llu (scale %llu)", n, b_scale);

    if (EXPECT_FALSE(b_scale < MIN_SCALE)) { b_scale = MIN_SCALE; }
    if (EXPECT_FALSE(b_scale > MAX_SCALE)) { return NULL; }

    LOCALIZE_THREAD_LOCAL(tid_, int);
    tl_t *tl = &tl_[tid_]; // thread-local data

    block_t *b = pop_free_list(tl, b_scale);
    if (b != NULL) {
        TRACE("m1", "nbd_malloc: returning block %p", b, 0);
        return b;
    //assert(b);
    }

    // The free list is empty so process blocks freed from other threads and then check again.
    process_incoming_blocks(tl);
    b = pop_free_list(tl, b_scale);
    if (b != NULL) {
        TRACE("m1", "nbd_malloc: returning block %p", b, 0);
        return b;
    //assert(b);
    }

#ifdef  RECYCLE_PAGES
    // The current active page is completely allocated. Make the oldest partially allocated page 
    // the new active page.
    size_class_t *sc = &tl->size_class[b_scale];
    if (sc->oldest_partial != NULL) {
        sc->active_page = sc->oldest_partial;
        sc->oldest_partial = sc->oldest_partial->next;
        sc->oldest_partial->prev = NULL;
        b = pop_free_list(tl, b_scale);
        //ASSERT(b != NULL);
        TRACE("m1", "nbd_malloc: returning block %p", b, 0);
        return b;
    //assert(b);
    }
    // There are no partially allocated pages so get a new page.

#endif//RECYCLE_PAGES

    // Get a new page.
    char *page = get_new_region(b_scale);
    b = (block_t *)page; // grab the first block on the page

    // Break up the remainder of the page into blocks and put them on the free list. Start at the
    // end of the page so that the free list ends up in increasing order, for ease of debugging.
    if (b_scale < PAGE_SCALE) {
        size_t block_size = (1ULL << b_scale);
        block_t *head = NULL;
        for (int offset = PAGE_SIZE - block_size; offset > 0; offset -= block_size) {
            block_t *x = (block_t *)(page + offset);
            x->next = head; head = x;
        }
#ifndef RECYCLE_PAGES
        tl->free_list[b_scale] = head;
#else //RECYCLE_PAGES
        sc->active_page = get_header(page);
        sc->active_page->free_list = head;
#endif//RECYCLE_PAGES
    }

    TRACE("m1", "nbd_malloc: returning block %p from new region %p", b, (size_t)b & ~MASK(PAGE_SCALE));
    //assert(b);
    return b;
}
#else//USE_SYSTEM_MALLOC
#include <stdlib.h>
#include "./include/common.h"
#include "./runtime/rlocal.h"
#include "./include/lwt.h"

void mem_init (void) {
    return;
}

void nbd_free (void *x) {
    TRACE("m1", "nbd_free: %p", x, 0);
#ifndef NDEBUG
    memset(x, 0xcd, sizeof(void *)); // bear trap
#endif//NDEBUG
    free(x);
    return;
}

void *nbd_malloc (size_t n) {
    TRACE("m1", "nbd_malloc: request size %llu", n, 0);
    void *x = malloc(n);
    TRACE("m1", "nbd_malloc: returning %p", x, 0);
    return x;
}
#endif//USE_SYSTEM_MALLOC
// ====
// END: runtime/mem.c
// ====

// ====
// BEGIN: datatype/nstring.c
// ====
#include "./include/common.h"
#include "./include/nstring.h"
#include "./include/murmur.h"
#include "./include/mem.h"

const datatype_t DATATYPE_NSTRING = { (cmp_fun_t)ns_cmp, (hash_fun_t)ns_hash, (clone_fun_t)ns_dup };

nstring_t *ns_alloc (uint32_t len) {
    nstring_t *ns = nbd_malloc(sizeof(nstring_t) + len);
    ns->len = len;
    return ns;
}

int ns_cmp (const nstring_t *ns1, const nstring_t *ns2) {
    int d = memcmp(ns1->data, ns2->data, (ns1->len < ns2->len) ? ns1->len : ns1->len);
    return (d == 0) ? ns1->len - ns2->len : d;
}

uint32_t ns_hash (const nstring_t *ns) {
    return murmur32(ns->data, ns->len);
}

nstring_t *ns_dup (const nstring_t *ns1) {
    nstring_t *ns2 = ns_alloc(ns1->len);
    memcpy(ns2->data, ns1->data, ns1->len);
    return ns2;
}
// ====
// END: datatype/nstring.c
// ====

// ====
// BEGIN: map/map.c
// ====
#if 0
/*
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 *
 * generic interface for map-like data structures
 */

#include "common.h"
#include "map.h"
#include "mem.h"

struct map {
    const map_impl_t *impl;
    void *data;
};

struct map_iter {
    const map_impl_t *impl;
    void *state;
};

map_t *map_alloc (const map_impl_t *map_impl, const datatype_t *key_type) {
    map_t *map = nbd_malloc(sizeof(map_t));
    map->impl  = map_impl;
    map->data  = map->impl->alloc(key_type);
    return map;
}

void map_free (map_t *map) {
    map->impl->free_(map->data);
}

void map_print (map_t *map, int verbose) {
    map->impl->print(map->data, verbose);
}

map_val_t map_count (map_t *map) {
    return map->impl->count(map->data);
}

map_val_t map_get (map_t *map, map_key_t key) {
    return map->impl->get(map->data, key);
}

map_val_t map_set (map_t *map, map_key_t key, map_val_t new_val) {
    return map->impl->cas(map->data, key, CAS_EXPECT_WHATEVER, new_val);
}

map_val_t map_add (map_t *map, map_key_t key, map_val_t new_val) {
    return map->impl->cas(map->data, key, CAS_EXPECT_DOES_NOT_EXIST, new_val);
}

map_val_t map_cas (map_t *map, map_key_t key, map_val_t expected_val, map_val_t new_val) {
    return map->impl->cas(map->data, key, expected_val, new_val);
}

map_val_t map_replace(map_t *map, map_key_t key, map_val_t new_val) {
    return map->impl->cas(map->data, key, CAS_EXPECT_EXISTS, new_val);
}

map_val_t map_remove (map_t *map, map_key_t key) {
    return map->impl->remove(map->data, key);
}

map_iter_t * map_iter_begin (map_t *map, map_key_t key) {
    map_iter_t *iter = nbd_malloc(sizeof(map_iter_t));
    iter->impl  = map->impl;
    iter->state = map->impl->iter_begin(map->data, key);
    return iter;
}

map_val_t map_iter_next (map_iter_t *iter, map_key_t *key_ptr) {
    return iter->impl->iter_next(iter->state, key_ptr);
}

void map_iter_free (map_iter_t *iter) {
    iter->impl->iter_free(iter->state);
    nbd_free(iter);
}
// ====
// END: map/map.c
// ====
#endif
//
// ====
// BEGIN: map/skiplist.c
// ====
/* 
 * Written by Josh Dybnis and released to the public domain, as explained at
 * http://creativecommons.org/licenses/publicdomain
 *
 * Harris-Michael lock-free list-based set
 * http://www.research.ibm.com/people/m/michael/spaa-2002.pdf
 */

#include <stdio.h>
#include <string.h>

#include "./include/common.h"
#include "./include/list.h"
#include "./include/mem.h"
#ifdef LIST_USE_HAZARD_POINTER
#include "./include/hazard.h"
#else
#include "./include/rcu.h"
#endif

typedef struct node {
    map_key_t  key;
    map_val_t  val;
    markable_t next; // next node
} node_t;

struct ll_iter {
    node_t *pred;
};

struct ll {
    node_t *head;
    const datatype_t *key_type;
};

// Marking the <next> field of a node logically removes it from the list
#define  MARK_NODE(x) TAG_VALUE((markable_t)(x), 0x1)
#define   HAS_MARK(x) (IS_TAGGED((x), 0x1) == 0x1)
#define   GET_NODE(x) ((node_t *)(x))
#define STRIP_MARK(x) ((node_t *)STRIP_TAG((x), 0x1))

static node_t *node_alloc (map_key_t key, map_val_t val) {
    node_t *item = (node_t *)nbd_malloc(sizeof(node_t));
    //assert(!HAS_MARK((size_t)item));
    item->key = key;
    item->val = val;
    return item;
}

list_t *ll_alloc (const datatype_t *key_type) {
    list_t *ll = (list_t *)nbd_malloc(sizeof(list_t));
    ll->key_type = key_type;
    ll->head = node_alloc(0, 0);
    ll->head->next = DOES_NOT_EXIST;
    return ll;
}

void ll_free (list_t *ll) {
    node_t *item = STRIP_MARK(ll->head->next);
    while (item != NULL) {
        node_t *next = STRIP_MARK(item->next);
        if (ll->key_type != NULL) {
            nbd_free((void *)item->key);
        }
        nbd_free(item);
        item = next;
    }
}

size_t ll_count (list_t *ll) {
    size_t count = 0;
    node_t *item = STRIP_MARK(ll->head->next);
    while (item) {
        if (!HAS_MARK(item->next)) {
            count++;
        }
        item = STRIP_MARK(item->next);
    }
    return count;
}

#ifdef LIST_USE_HAZARD_POINTER
static void nbd_free_node (node_t *x) {
    nbd_free((void *)x->key);
    nbd_free(x);
}
#endif

static int find_pred (node_t **pred_ptr, node_t **item_ptr, list_t *ll, map_key_t key, int help_remove) {
    node_t *pred = ll->head;
    node_t *item = GET_NODE(pred->next);
    TRACE("l2", "find_pred: searching for key %p in list (head is %p)", key, pred);
#ifdef LIST_USE_HAZARD_POINTER
    haz_t *temp, *hp0 = haz_get_static(0), *hp1 = haz_get_static(1);
#endif

    while (item != NULL) {
#ifdef LIST_USE_HAZARD_POINTER
        haz_set(hp0, item);
        if (STRIP_MARK(pred->next) != item)
            return find_pred(pred_ptr, item_ptr, ll, key, help_remove); // retry
#endif
        markable_t next = item->next;

        // A mark means the node is logically removed but not physically unlinked yet.
        while (EXPECT_FALSE(HAS_MARK(next))) {

            // Skip over logically removed items.
            if (!help_remove) {
                item = STRIP_MARK(item->next);
                if (EXPECT_FALSE(item == NULL))
                    break;
                TRACE("l3", "find_pred: skipping marked item %p (next is %p)", item, next);
                next = item->next;
                continue;
            }

            // Unlink logically removed items.
            TRACE("l3", "find_pred: unlinking marked item %p next is %p", item, next);

            markable_t other = SYNC_CAS(&pred->next, (markable_t)item, (markable_t)STRIP_MARK(next));
            if (other == (markable_t)item) {
                TRACE("l2", "find_pred: unlinked item %p from pred %p", item, pred);
                item = STRIP_MARK(next);
                next = (item != NULL) ? item->next : DOES_NOT_EXIST;
                TRACE("l3", "find_pred: now current item is %p next is %p", item, next);

                // The thread that completes the unlink should free the memory.
#ifdef LIST_USE_HAZARD_POINTER
                free_t free_ = (ll->key_type != NULL ? (free_t)nbd_free_node : nbd_free);
                haz_defer_free(GET_NODE(other), free_);
#else
                if (ll->key_type != NULL) {
                    rcu_defer_free((void *)GET_NODE(other)->key);
                }
                rcu_defer_free(GET_NODE(other));
#endif
            } else {
                TRACE("l2", "find_pred: lost a race to unlink item %p from pred %p", item, pred);
                TRACE("l2", "find_pred: pred's link changed to %p", other, 0);
                if (HAS_MARK(other))
                    return find_pred(pred_ptr, item_ptr, ll, key, help_remove); // retry
                item = GET_NODE(other);
                next = (item != NULL) ? item->next : DOES_NOT_EXIST;
            }
        }

        if (EXPECT_FALSE(item == NULL))
            break;

        TRACE("l3", "find_pred: visiting item %p (next is %p)", item, next);
        TRACE("l4", "find_pred: key %p val %p", item->key, item->val);

        int d;
        if (EXPECT_TRUE(ll->key_type == NULL)) {
            d = item->key - key;
        } 
#if 0
        else {
            d = ll->key_type->cmp((void *)item->key, (void *)key);
        }
#endif

        // If we reached the key (or passed where it should be), we found the right predesssor
        if (d >= 0) {
            if (pred_ptr != NULL) {
                *pred_ptr = pred;
            }
            if (item_ptr != NULL) {
                *item_ptr = item;
            }
            if (d == 0) {
                TRACE("l2", "find_pred: found matching item %p in list, pred is %p", item, pred);
                return TRUE;
            } 
            TRACE("l2", "find_pred: found proper place for key %p in list, pred is %p", key, pred);
            return FALSE;
        }

        pred = item;
#ifdef LIST_USE_HAZARD_POINTER
        temp = hp0; hp0 = hp1; hp1 = temp;
#endif
        item = GET_NODE(next);
    }

    // <key> is not in <ll>.
    if (pred_ptr != NULL) {
        *pred_ptr = pred;
    }
    *item_ptr = NULL;
    TRACE("l2", "find_pred: reached end of list. last item is %p", pred, 0);
    return FALSE;
}

// Fast find. Do not help unlink partially removed nodes and do not return the found item's predecessor.
map_val_t ll_lookup (list_t *ll, map_key_t key) {
    TRACE("l1", "ll_lookup: searching for key %p in list %p", key, ll);
    node_t *item;
    int found = find_pred(NULL, &item, ll, key, FALSE);

    // If we found an <item> matching the key return its value.
    if (found) {
        map_val_t val = item->val;
        if (val != DOES_NOT_EXIST) {
            TRACE("l1", "ll_lookup: found item %p. val %p. returning item", item, item->val);
            return val;
        }
    }

    TRACE("l1", "ll_lookup: no item in the list matched the key", 0, 0);
    return DOES_NOT_EXIST;
}

map_val_t ll_cas (list_t *ll, map_key_t key, map_val_t expectation, map_val_t new_val) {
    TRACE("l1", "ll_cas: key %p list %p", key, ll);
    TRACE("l1", "ll_cas: expectation %p new value %p", expectation, new_val);
    //ASSERT((int64_t)new_val > 0);

    do {
        node_t *pred, *old_item;
        int found = find_pred(&pred, &old_item, ll, key, TRUE);
        if (!found) {

            // There was not an item in the list that matches the key. 
            if (EXPECT_FALSE(expectation != CAS_EXPECT_DOES_NOT_EXIST && expectation != CAS_EXPECT_WHATEVER)) {
                TRACE("l1", "ll_cas: the expectation was not met, the list was not changed", 0, 0);
                return DOES_NOT_EXIST; // failure
            }

            // Create a new item and insert it into the list.
            TRACE("l2", "ll_cas: attempting to insert item between %p and %p", pred, pred->next);
            map_key_t new_key = key;
            node_t *new_item = node_alloc(new_key, new_val);
            markable_t next = new_item->next = (markable_t)old_item;
            markable_t other = SYNC_CAS(&pred->next, (markable_t)next, (markable_t)new_item);
            if (other == next) {
                TRACE("l1", "ll_cas: successfully inserted new item %p", new_item, 0);
                return DOES_NOT_EXIST; // success
            }

            // Lost a race. Failed to insert the new item into the list.
            TRACE("l1", "ll_cas: lost a race. CAS failed. expected pred's link to be %p but found %p", next, other);
            if (ll->key_type != NULL) {
                nbd_free((void *)new_key);
            }
            nbd_free(new_item);
            continue; // retry
        }

        // Found an item in the list that matches the key.
        map_val_t old_item_val = old_item->val;
        do {
            // If the item's value is DOES_NOT_EXIST it means another thread removed the node out from under us.
            if (EXPECT_FALSE(old_item_val == DOES_NOT_EXIST)) {
                TRACE("l2", "ll_cas: lost a race, found an item but another thread removed it. retry", 0, 0);
                break; // retry
            }

            if (EXPECT_FALSE(expectation == CAS_EXPECT_DOES_NOT_EXIST)) {
                TRACE("l1", "ll_cas: found an item %p in the list that matched the key. the expectation was "
                        "not met, the list was not changed", old_item, old_item_val);
                return old_item_val; // failure
            }

            // Use a CAS and not a SWAP. If the node is in the process of being removed and we used a SWAP, we could
            // replace DOES_NOT_EXIST with our value. Then another thread that is updating the value could think it
            // succeeded and return our value even though we indicated that the node has been removed. If the CAS 
            // fails it means another thread either removed the node or updated its value.
            map_val_t ret_val = SYNC_CAS(&old_item->val, old_item_val, new_val);
            if (ret_val == old_item_val) {
                TRACE("l1", "ll_cas: the CAS succeeded. updated the value of the item", 0, 0);
                return ret_val; // success
            }
            TRACE("l2", "ll_cas: lost a race. the CAS failed. another thread changed the item's value", 0, 0);

            old_item_val = ret_val;
        } while (1);
    } while (1);
}

map_val_t ll_remove (list_t *ll, map_key_t key) {
    TRACE("l1", "ll_remove: removing item with key %p from list %p", key, ll);
    node_t *pred;
    node_t *item;
    int found = find_pred(&pred, &item, ll, key, TRUE);
    if (!found) {
        TRACE("l1", "ll_remove: remove failed, an item with a matching key does not exist in the list", 0, 0);
        return DOES_NOT_EXIST;
    }

    // Mark <item> removed. If multiple threads try to remove the same item only one of them should succeed.
    markable_t next;
    markable_t old_next = item->next;
    do {
        next     = old_next;
        old_next = SYNC_CAS(&item->next, next, MARK_NODE(STRIP_MARK(next)));
        if (HAS_MARK(old_next)) {
            TRACE("l1", "ll_remove: lost a race -- %p is already marked for removal by another thread", item, 0);
            return DOES_NOT_EXIST;
        }
    } while (next != old_next);
    TRACE("l2", "ll_remove: logically removed item %p", item, 0);
    //ASSERT(HAS_MARK(VOLATILE_DEREF(item).next));

    // Atomically swap out the item's value in case another thread is updating the item while we are 
    // removing it. This establishes which operation occurs first logically, the update or the remove. 
    map_val_t val = SYNC_SWAP(&item->val, DOES_NOT_EXIST); 
    TRACE("l2", "ll_remove: replaced item's val %p with DOES_NOT_EXIT", val, 0);

    // Unlink <item> from <ll>. If we lose a race to another thread just back off. It is safe to leave the
    // item logically removed for a later call (or some other thread) to physically unlink. By marking the
    // item earlier, we logically removed it. 
    TRACE("l2", "ll_remove: unlink the item by linking its pred %p to its successor %p", pred, next);
    markable_t other;
    if ((other = SYNC_CAS(&pred->next, (markable_t)item, next)) != (markable_t)item) {
        TRACE("l1", "ll_remove: unlink failed; pred's link changed from %p to %p", item, other);
        return val;
    } 

    // The thread that completes the unlink should free the memory.
#ifdef LIST_USE_HAZARD_POINTER
    free_t free_ = (ll->key_type != NULL ? (free_t)nbd_free_node : nbd_free);
    haz_defer_free(GET_NODE(item), free_);
#else
    if (ll->key_type != NULL) {
        rcu_defer_free((void *)item->key);
    }
    rcu_defer_free(item);
#endif
    TRACE("l1", "ll_remove: successfully unlinked item %p from the list", item, 0);
    return val;
}

void ll_print (list_t *ll, int verbose) {
    if (verbose) {
        markable_t next = ll->head->next;
        int i = 0;
        while (next != DOES_NOT_EXIST) {
            node_t *item = STRIP_MARK(next);
            if (item == NULL)
                break;
            printf("%s%p:0x%llx ", HAS_MARK(item->next) ? "*" : "", item, (uint64_t)item->key);
            fflush(stdout);
            if (i++ > 30) {
                printf("...");
                break;
            }
            next = item->next;
        }
        printf("\n");
    }
    printf("count:%llu\n", (uint64_t)ll_count(ll));
}

ll_iter_t *ll_iter_begin (list_t *ll, map_key_t key) {
    ll_iter_t *iter = (ll_iter_t *)nbd_malloc(sizeof(ll_iter_t));
    if (key != DOES_NOT_EXIST) {
        find_pred(&iter->pred, NULL, ll, key, FALSE);
    } else {
        iter->pred = ll->head;
    }
#ifdef LIST_USE_HAZARD_POINTER
    haz_register_dynamic((void **)&iter->pred);
#endif
    return iter;
}

map_val_t ll_iter_next (ll_iter_t *iter, map_key_t *key_ptr) {
    //assert(iter);
    if (iter->pred == NULL)
        return DOES_NOT_EXIST;

    // advance iterator to next item; skip items that have been removed
    markable_t item;
#ifdef LIST_USE_HAZARD_POINTER 
    haz_t *hp0 = haz_get_static(0);
#endif
    do {
#ifndef LIST_USE_HAZARD_POINTER 
        item = iter->pred->next;
#else //LIST_USE_HAZARD_POINTER 
        do {
            item = iter->pred->next;
            haz_set(hp0, STRIP_MARK(item));
        } while (item != VOLATILE_DEREF(iter->pred).next);
#endif//LIST_USE_HAZARD_POINTER
        iter->pred = STRIP_MARK(item);
        if (iter->pred == NULL)
            return DOES_NOT_EXIST;
    } while (HAS_MARK(item));

    if (key_ptr != NULL) {
        *key_ptr = GET_NODE(item)->key;
    }
    return GET_NODE(item)->val;
}

void ll_iter_free (ll_iter_t *iter) {
#ifdef LIST_USE_HAZARD_POINTER
    haz_unregister_dynamic((void **)&iter->pred);
#endif
    nbd_free(iter);
}
// ====
// END: map/list.c
// ====


// ===
// BEGIN: map/skiplist.c
// ===
#include <stdio.h>
#include <string.h>

#include "./include/common.h"
#include "./include/skiplist.h"
#include "./include/runtime.h"
#include "./include/mem.h"
#include "./include/rcu.h"

// Setting MAX_LEVELS to 1 essentially makes this data structure the Harris-Michael lock-free list (see list.c).
#define MAX_LEVELS 24

enum unlink {
    FORCE_UNLINK,
    ASSIST_UNLINK,
    DONT_UNLINK
};

typedef struct node_sl {
    map_key_t key;
    map_val_t val;
    unsigned num_levels;
    markable_t next[1];
} node_sl_t;

struct sl_iter {
    node_sl_t *next;
};

struct sl {
    node_sl_t *head;
    const datatype_t *key_type;
    int high_water; // max historic number of levels
};

// Marking the <next> field of a node logically removes it from the list
#if 0
static inline markable_t  MARK_NODE(node_t * x) { return TAG_VALUE((markable_t)x, 0x1); }
static inline int        HAS_MARK(markable_t x) { return (IS_TAGGED(x, 0x1) == 0x1); }
static inline node_t *   GET_SL_NODE(markable_t x) { assert(!HAS_MARK(x)); return (node_t *)x; }
static inline node_t * STRIP_SL_MARK(markable_t x) { return ((node_t *)STRIP_TAG(x, 0x1)); }
#else
#define  MARK_NODE(x) TAG_VALUE((markable_t)(x), 0x1)
#define   HAS_MARK(x) (IS_TAGGED((x), 0x1) == 0x1)
#define   GET_SL_NODE(x) ((node_sl_t *)(x))
#define STRIP_SL_MARK(x) ((node_sl_t *)STRIP_TAG((x), 0x1))
#endif

static int random_levels (skiplist_t *sl) {
    uint64_t r = nbd_rand();
    int z = __builtin_ctz(r);
    int levels = (int)(z / 1.5);
    if (levels == 0)
        return 1;
    if (levels > sl->high_water) {
        levels = SYNC_ADD(&sl->high_water, 1);
        TRACE("s2", "random_levels: increased high water mark to %lld", sl->high_water, 0);
    }
    if (levels > MAX_LEVELS) { levels = MAX_LEVELS; }
    return levels;
}

static node_sl_t *node_sl_alloc (int num_levels, map_key_t key, map_val_t val) {
    assert(num_levels >= 0 && num_levels <= MAX_LEVELS);
    size_t sz = sizeof(node_sl_t) + (num_levels - 1) * sizeof(node_sl_t *);
    node_sl_t *item = (node_sl_t *)nbd_malloc(sz);
    memset(item, 0, sz);
    item->key = key;
    item->val = val;
    item->num_levels = num_levels;
    TRACE("s2", "node_sl_alloc: new node %p (%llu levels)", item, num_levels);
    return item;
}

skiplist_t *sl_alloc (const datatype_t *key_type) {
    skiplist_t *sl = (skiplist_t *)nbd_malloc(sizeof(skiplist_t));
    sl->key_type = key_type;
    sl->high_water = 1;
    sl->head = node_sl_alloc(MAX_LEVELS, 0, 0);
    memset(sl->head->next, 0, MAX_LEVELS * sizeof(skiplist_t *));
    return sl;
}

void sl_free (skiplist_t *sl) {
    node_sl_t *item = GET_SL_NODE(sl->head->next[0]);
    while (item) {
        node_sl_t *next = STRIP_SL_MARK(item->next[0]);
        if (sl->key_type != NULL) {
            nbd_free((void *)item->key);
        }
        nbd_free(item);
        item = next;
    }
}

size_t sl_count (skiplist_t *sl) {
    size_t count = 0;
    node_sl_t *item = GET_SL_NODE(sl->head->next[0]);
    while (item) {
        if (!HAS_MARK(item->next[0])) {
            count++;
        }
        item = STRIP_SL_MARK(item->next[0]);
    }
    return count;
}

static node_sl_t *find_preds (node_sl_t **preds, node_sl_t **succs, int n, skiplist_t *sl, map_key_t key, enum unlink unlink) {
    node_sl_t *pred = sl->head;
    node_sl_t *item = NULL;
    TRACE("s2", "find_preds: searching for key %p in skiplist (head is %p)", key, pred);
    int d = 0;

    // Traverse the levels of <sl> from the top level to the bottom
    for (int level = sl->high_water - 1; level >= 0; --level) {
        markable_t next = pred->next[level];
        if (next == DOES_NOT_EXIST && level >= n)
            continue;
        TRACE("s3", "find_preds: traversing level %p starting at %p", level, pred);
        if (EXPECT_FALSE(HAS_MARK(next))) {
            TRACE("s2", "find_preds: pred %p is marked for removal (next %p); retry", pred, next);
            ASSERT(level == pred->num_levels - 1 || HAS_MARK(pred->next[level+1]));
            return find_preds(preds, succs, n, sl, key, unlink); // retry
        }
        item = GET_SL_NODE(next);
        while (item != NULL) {
            next = item->next[level];

            // A tag means an item is logically removed but not physically unlinked yet.
            while (EXPECT_FALSE(HAS_MARK(next))) {
                TRACE("s3", "find_preds: found marked item %p (next is %p)", item, next);
                if (unlink == DONT_UNLINK) {

                    // Skip over logically removed items.
                    item = STRIP_SL_MARK(next);
                    if (EXPECT_FALSE(item == NULL))
                        break;
                    next = item->next[level];
                } else {

                    // Unlink logically removed items.
                    markable_t other = SYNC_CAS(&pred->next[level], (markable_t)item, (markable_t)STRIP_SL_MARK(next));
                    if (other == (markable_t)item) {
                        TRACE("s3", "find_preds: unlinked item from pred %p", pred, 0);
                        item = STRIP_SL_MARK(next);
                    } else {
                        TRACE("s3", "find_preds: lost race to unlink item pred %p's link changed to %p", pred, other);
                        if (HAS_MARK(other))
                            return find_preds(preds, succs, n, sl, key, unlink); // retry
                        item = GET_SL_NODE(other);
                    }
                    next = (item != NULL) ? item->next[level] : DOES_NOT_EXIST;
                }
            }

            if (EXPECT_FALSE(item == NULL)) {
                TRACE("s3", "find_preds: past the last item in the skiplist", 0, 0);
                break;
            }

            TRACE("s4", "find_preds: visiting item %p (next is %p)", item, next);
            TRACE("s4", "find_preds: key %p val %p", STRIP_SL_MARK(item->key), item->val);

            if (EXPECT_TRUE(sl->key_type == NULL)) {
                d = item->key - key;
            } 
            
#if 0
            else {
                d = sl->key_type->cmp((void *)item->key, (void *)key);
            }
#endif

            if (d > 0)
                break;
            if (d == 0 && unlink != FORCE_UNLINK)
                break;

            pred = item;
            item = GET_SL_NODE(next);
        }

        TRACE("s3", "find_preds: found pred %p next %p", pred, item);

        if (level < n) {
            if (preds != NULL) {
                preds[level] = pred;
            }
            if (succs != NULL) {
                succs[level] = item;
            }
        }
    }

    if (d == 0) {
        TRACE("s2", "find_preds: found matching item %p in skiplist, pred is %p", item, pred);
        return item;
    }
    TRACE("s2", "find_preds: found proper place for key %p in skiplist, pred is %p. returning null", key, pred);
    return NULL;
}

// Fast find that does not help unlink partially removed nodes and does not return the node's predecessors.
map_val_t sl_lookup (skiplist_t *sl, map_key_t key) {
    TRACE("s1", "sl_lookup: searching for key %p in skiplist %p", key, sl);
    node_sl_t *item = find_preds(NULL, NULL, 0, sl, key, DONT_UNLINK);

    // If we found an <item> matching the <key> return its value.
    if (item != NULL) {
        map_val_t val = item->val;
        if (val != DOES_NOT_EXIST) {
            TRACE("s1", "sl_lookup: found item %p. val %p. returning item", item, item->val);
            return val;
        }
    }

    TRACE("s1", "sl_lookup: no item in the skiplist matched the key", 0, 0);
    return DOES_NOT_EXIST;
}

map_key_t sl_min_key (skiplist_t *sl) {
    node_sl_t *item = GET_SL_NODE(sl->head->next[0]);
    while (item != NULL) {
        markable_t next = item->next[0];
        if (!HAS_MARK(next))
            return item->key;
        item = STRIP_SL_MARK(next);
    }
    return DOES_NOT_EXIST;
}

static map_val_t update_item (node_sl_t *item, map_val_t expectation, map_val_t new_val) {
    map_val_t old_val = item->val;

    // If the item's value is DOES_NOT_EXIST it means another thread removed the node out from under us.
    if (EXPECT_FALSE(old_val == DOES_NOT_EXIST)) {
        TRACE("s2", "update_item: lost a race to another thread removing the item. retry", 0, 0);
        return DOES_NOT_EXIST; // retry
    }

    if (EXPECT_FALSE(expectation == CAS_EXPECT_DOES_NOT_EXIST)) {
        TRACE("s1", "update_item: the expectation was not met; the skiplist was not changed", 0, 0);
        return old_val; // failure
    }

    // Use a CAS and not a SWAP. If the CAS fails it means another thread removed the node or updated its
    // value. If another thread removed the node but it is not unlinked yet and we used a SWAP, we could
    // replace DOES_NOT_EXIST with our value. Then another thread that is updating the value could think it
    // succeeded and return our value even though it should return DOES_NOT_EXIST.
    if (old_val == SYNC_CAS(&item->val, old_val, new_val)) {
        TRACE("s1", "update_item: the CAS succeeded. updated the value of the item", 0, 0);
        return old_val; // success
    }
    TRACE("s2", "update_item: lost a race. the CAS failed. another thread changed the item's value", 0, 0);

    // retry
    return update_item(item, expectation, new_val); // tail call
}

map_val_t sl_cas (skiplist_t *sl, map_key_t key, map_val_t expectation, map_val_t new_val) {
    TRACE("s1", "sl_cas: key %p skiplist %p", key, sl);
    TRACE("s1", "sl_cas: expectation %p new value %p", expectation, new_val);
    ASSERT((int64_t)new_val > 0);

    node_sl_t *preds[MAX_LEVELS];
    node_sl_t *nexts[MAX_LEVELS];
    node_sl_t *new_item = NULL;
    int n = random_levels(sl);
    node_sl_t *old_item = find_preds(preds, nexts, n, sl, key, ASSIST_UNLINK);

    // If there is already an item in the skiplist that matches the key just update its value.
    if (old_item != NULL) {
        map_val_t ret_val = update_item(old_item, expectation, new_val);
        if (ret_val != DOES_NOT_EXIST)
            return ret_val;

        // If we lose a race with a thread removing the item we tried to update then we have to retry.
        return sl_cas(sl, key, expectation, new_val); // tail call
    }

    if (EXPECT_FALSE(expectation != CAS_EXPECT_DOES_NOT_EXIST && expectation != CAS_EXPECT_WHATEVER)) {
        TRACE("s1", "sl_cas: the expectation was not met, the skiplist was not changed", 0, 0);
        return DOES_NOT_EXIST; // failure, the caller expected an item for the <key> to already exist
    }

    // Create a new node and insert it into the skiplist.
    TRACE("s3", "sl_cas: attempting to insert a new item between %p and %p", preds[0], nexts[0]);
    map_key_t new_key = key;
    new_item = node_sl_alloc(n, new_key, new_val);

    // Set <new_item>'s next pointers to their proper values
    markable_t next = new_item->next[0] = (markable_t)nexts[0];
    for (int level = 1; level < new_item->num_levels; ++level) {
        new_item->next[level] = (markable_t)nexts[level];
    }

    // Link <new_item> into <sl> from the bottom level up. After <new_item> is inserted into the bottom level
    // it is officially part of the skiplist.
    node_sl_t *pred = preds[0];
    markable_t other = SYNC_CAS(&pred->next[0], next, (markable_t)new_item);
    if (other != next) {
        TRACE("s3", "sl_cas: failed to change pred's link: expected %p found %p", next, other);

        // Lost a race to another thread modifying the skiplist. Free the new item we allocated and retry.
        if (sl->key_type != NULL) {
            nbd_free((void *)new_key);
        }
        nbd_free(new_item);
        return sl_cas(sl, key, expectation, new_val); // tail call
    }

    TRACE("s3", "sl_cas: successfully inserted a new item %p at the bottom level", new_item, 0);

    ASSERT(new_item->num_levels <= MAX_LEVELS);
    for (int level = 1; level < new_item->num_levels; ++level) {
        TRACE("s3", "sl_cas: inserting the new item %p at level %p", new_item, level);
        do {
            node_sl_t *   pred = preds[level];
            ASSERT(new_item->next[level]==(markable_t)nexts[level] || new_item->next[level]==MARK_NODE(nexts[level]));
            TRACE("s3", "sl_cas: attempting to to insert the new item between %p and %p", pred, nexts[level]);

            markable_t other = SYNC_CAS(&pred->next[level], (markable_t)nexts[level], (markable_t)new_item);
            if (other == (markable_t)nexts[level])
                break; // successfully linked <new_item> into the skiplist at the current <level>
            TRACE("s3", "sl_cas: lost a race. failed to change pred's link. expected %p found %p", nexts[level], other);

            // Find <new_item>'s new preds and nexts.
            find_preds(preds, nexts, new_item->num_levels, sl, key, ASSIST_UNLINK);

            for (int i = level; i < new_item->num_levels; ++i) {
                markable_t old_next = new_item->next[i];
                if ((markable_t)nexts[i] == old_next)
                    continue;

                // Update <new_item>'s inconsistent next pointer before trying again. Use a CAS so if another thread
                // is trying to remove the new item concurrently we do not stomp on the mark it places on the item.
                TRACE("s3", "sl_cas: attempting to update the new item's link from %p to %p", old_next, nexts[i]);
                other = SYNC_CAS(&new_item->next[i], old_next, (markable_t)nexts[i]);
                ASSERT(other == old_next || other == MARK_NODE(old_next));

                // If another thread is removing this item we can stop linking it into to skiplist
                if (HAS_MARK(other)) {
                    find_preds(NULL, NULL, 0, sl, key, FORCE_UNLINK); // see comment below
                    return DOES_NOT_EXIST;
                }
            }
        } while (1);
    }

    // In case another thread was in the process of removing the <new_item> while we were added it, we have to
    // make sure it is completely unlinked before we return. We might have lost a race and inserted the new item
    // at some level after the other thread thought it was fully removed. That is a problem because once a thread
    // thinks it completely unlinks a node it queues it to be freed
    if (HAS_MARK(new_item->next[new_item->num_levels - 1])) {
        find_preds(NULL, NULL, 0, sl, key, FORCE_UNLINK);
    }

    return DOES_NOT_EXIST; // success, inserted a new item
}

map_val_t sl_remove (skiplist_t *sl, map_key_t key) {
    TRACE("s1", "sl_remove: removing item with key %p from skiplist %p", key, sl);
    node_sl_t *preds[MAX_LEVELS];
    node_sl_t *item = find_preds(preds, NULL, sl->high_water, sl, key, ASSIST_UNLINK);
    if (item == NULL) {
        TRACE("s3", "sl_remove: remove failed, an item with a matching key does not exist in the skiplist", 0, 0);
        return DOES_NOT_EXIST;
    }

    // Mark <item> at each level of <sl> from the top down. If multiple threads try to concurrently remove
    // the same item only one of them should succeed. Marking the bottom level establishes which of them succeeds.
    markable_t old_next = 0;
    for (int level = item->num_levels - 1; level >= 0; --level) {
        markable_t next;
        old_next = item->next[level];
        do {
            TRACE("s3", "sl_remove: marking item at level %p (next %p)", level, old_next);
            next = old_next;
            old_next = SYNC_CAS(&item->next[level], next, MARK_NODE((node_sl_t *)next));
            if (HAS_MARK(old_next)) {
                TRACE("s2", "sl_remove: %p is already marked for removal by another thread (next %p)", item, old_next);
                if (level == 0)
                    return DOES_NOT_EXIST;
                break;
            }
        } while (next != old_next);
    }

    // Atomically swap out the item's value in case another thread is updating the item while we are
    // removing it. This establishes which operation occurs first logically, the update or the remove.
    map_val_t val = SYNC_SWAP(&item->val, DOES_NOT_EXIST);
    TRACE("s2", "sl_remove: replaced item %p's value with DOES_NOT_EXIT", item, 0);

    // unlink the item
    find_preds(NULL, NULL, 0, sl, key, FORCE_UNLINK);

    // free the node
    if (sl->key_type != NULL) {
        rcu_defer_free((void *)item->key);
    }
    rcu_defer_free(item);

    return val;
}

void sl_print (skiplist_t *sl, int verbose) {

    if (verbose) {
        for (int level = MAX_LEVELS - 1; level >= 0; --level) {
            node_sl_t *item = sl->head;
            if (item->next[level] == DOES_NOT_EXIST)
                continue;
            printf("(%d) ", level);
            int i = 0;
            while (item) {
                markable_t next = item->next[level];
                printf("%s%p ", HAS_MARK(next) ? "*" : "", item);
                item = STRIP_SL_MARK(next);
                if (i++ > 30) {
                    printf("...");
                    break;
                }
            }
            printf("\n");
            fflush(stdout);
        }
        node_sl_t *item = sl->head;
        int i = 0;
        while (item) {
            int is_marked = HAS_MARK(item->next[0]);
            printf("%s%p:0x%llx ", is_marked ? "*" : "", item, (uint64_t)item->key);
            if (item != sl->head) {
                printf("[%d]", item->num_levels);
            } else {
                printf("[HEAD]");
            }
            for (int level = 1; level < item->num_levels; ++level) {
                node_sl_t *next = STRIP_SL_MARK(item->next[level]);
                is_marked = HAS_MARK(item->next[0]);
                printf(" %p%s", next, is_marked ? "*" : "");
                if (item == sl->head && item->next[level] == DOES_NOT_EXIST)
                    break;
            }
            printf("\n");
            fflush(stdout);
            item = STRIP_SL_MARK(item->next[0]);
            if (i++ > 30) {
                printf("...\n");
                break;
            }
        }
    }
    printf("levels:%-2d  count:%-6lld \n", sl->high_water, (uint64_t)sl_count(sl));
}

sl_iter_t *sl_iter_begin (skiplist_t *sl, map_key_t key) {
    sl_iter_t *iter = (sl_iter_t *)nbd_malloc(sizeof(sl_iter_t));
    if (key != DOES_NOT_EXIST) {
        find_preds(NULL, &iter->next, 1, sl, key, DONT_UNLINK);
    } else {
        iter->next = GET_SL_NODE(sl->head->next[0]);
    }
    return iter;
}

map_val_t sl_iter_next (sl_iter_t *iter, map_key_t *key_ptr) {
    assert(iter);
    node_sl_t *item = iter->next;
    while (item != NULL && HAS_MARK(item->next[0])) {
        item = STRIP_SL_MARK(item->next[0]);
    }
    if (item == NULL) {
        iter->next = NULL;
        return DOES_NOT_EXIST;
    }
    iter->next = STRIP_SL_MARK(item->next[0]);
    if (key_ptr != NULL) {
        *key_ptr = item->key;
    }
    return item->val;
}

void sl_iter_free (sl_iter_t *iter) {
    nbd_free(iter);
}
// ===
// END: map/skiplist.c
// ===
