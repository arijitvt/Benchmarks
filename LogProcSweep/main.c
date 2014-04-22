#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct list_node_st {
  const char *log_entry;    /**< Data to be stored in the node */
  list_node *next;  /**< Next pointer for the linked list */
};

typedef struct {
  list_node log_entry_list; /**< Head node of the list */
  int num_entries;  /**< Number of entries in the list */
  pthread_mutex_t lock;	/**< Lock to synchronize access to the list */
} log_type;

log_type *shared_log = NULL;

pthread_mutex_t mem_lock;

list_node *new_log_entry() {
  pthread_mutex_lock(&mem_lock);
  list_node *node = malloc(sizeof(list_node));
  pthread_mutex_unlock(&mem_lock);
  return node;
}

void add_log_entry(log_type *log, const char *entry) {
  list_node *node = new_log_entry();
  node->log_entry = entry;

  pthread_mutex_lock(&log->lock);

  node->next = log->log_entry_list.next;    
  log->log_entry_list.next = node;

  log->num_entries++;
  pthread_mutex_unlock(&log->lock);
}

void init_log(log_type *log) {
  log->log_entry_list.log_entry = "HEAD";
  log->log_entry_list.next = NULL;
  log->num_entries = 0;
  pthread_mutex_init(&log->lock, NULL);
}

void logging(const char *entry) {
	int pre = shared_log->num_entries;
  if (shared_log) {
    add_log_entry(shared_log, entry);
    int post = shared_log->num_entries;
  }
}

void *t1_main(void *args) {
  logging("LOG");
  return NULL;
}

void *t2_main(void *args) {
  shared_log = malloc(sizeof(log_type));
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_mutex_init(&mem_lock, NULL);
  shared_log = malloc(sizeof(log_type));
  init_log(shared_log);

  pthread_t *tids = malloc(sizeof(pthread_t) * 2);
  pthread_create(&tids[0], NULL, t1_main, NULL);
  pthread_create(&tids[1], NULL, t2_main, NULL);
  pthread_join(tids[0], NULL);
  pthread_join(tids[1], NULL);

  return 0;
}

