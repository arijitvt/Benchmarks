#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct list_node_st list_node;
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


/*
===========================================================================
..new_log_entry():::ENTER
new_log_entry() is only ever called after main initializes shared_log
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
===========================================================================
..new_log_entry():::EXIT
none of the globals are modified
::shared_log == orig(::shared_log)
::.str == orig(::.str)
::.str1 == orig(::.str1)
::.str2 == orig(::.str2)
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
return != null
===========================================================================
*/
list_node *new_log_entry() {
  pthread_mutex_lock(&mem_lock);
  list_node *node = malloc(sizeof(list_node));
  pthread_mutex_unlock(&mem_lock);
  return node;
}

/*
===========================================================================
..add_log_entry():::ENTER
add_log_entry() is only ever called with shared log
::shared_log == log
add_log_entry is called only after main initializes shared_log
::shared_log != null
the string constants are never modified
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
entry is only ever called with the non-null const string "LOG"
entry1 has only one value
entry1 != null
===========================================================================
..add_log_entry():::EXIT
add_log_entry() does not modify the global shared_log or the argument log.
::shared_log == orig(::shared_log)
::shared_log == orig(log)
string constants are never modified
::.str == orig(::.str)
::.str1 == orig(::.str1)
::.str2 == orig(::.str2)
shared log is initialized before add_log_entry is called
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
===========================================================================
*/
void add_log_entry(log_type *log, const char *entry) {
  list_node *node = new_log_entry();
  node->log_entry = entry;

  pthread_mutex_lock(&log->lock);

  node->next = log->log_entry_list.next;    
  log->log_entry_list.next = node;

  log->num_entries++;
  pthread_mutex_unlock(&log->lock);
}

/*
===========================================================================
..init_log():::ENTER
These are true. Shared log is a pointer initialized by main (via malloc()). its
address never changes
::shared_log has only one value
::shared_log != null
str and str1 are the constant strings ("HEAD" and "LOG").
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
log != null
===========================================================================
..init_log():::EXIT
This function does not modify the log or the string so these are good to go. It
only modifies the internal values in the log (which are not tracked, currently)
::shared_log == orig(::shared_log)
::.str == orig(::.str)
::.str1 == orig(::.str1)
::shared_log has only one value
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
===========================================================================
 */
void init_log(log_type *log) {
  log->log_entry_list.log_entry = "HEAD";
  log->log_entry_list.next = NULL;
  log->num_entries = 0;
  pthread_mutex_init(&log->lock, NULL);
}

/*
 *
===========================================================================
..logging():::ENTER
logging() is only called after main() initialies shared_log
::shared_log != null
string constants are never modified
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
logging is only ever called with the const non-null string "LOG"
entry1 has only one value
entry1 != null
===========================================================================
..logging():::EXIT
none of the globals are modified
::.str == orig(::.str)
::.str1 == orig(::.str1)
::.str2 == orig(::.str2)
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
===========================================================================
*/
void logging(const char *entry) {
	int pre = shared_log->num_entries;
  if (shared_log) {
    add_log_entry(shared_log, entry);
    int post = shared_log->num_entries;
  }
}


/*
===========================================================================
..t1_main():::ENTER
t1_main() is called after main initializes the log
::shared_log != null
constants are never modified
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
t1_main is only ever called with NULL
args == null
===========================================================================
..t1_main():::EXIT
t1 main doesn't modify the stings
::.str == orig(::.str)
::.str1 == orig(::.str1)
::.str2 == orig(::.str2)
thread always returns NULL
return == orig(args)
shared log is not set to NULL
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
always returns NULL
return == null
*/
void *t1_main(void *args) {
  logging("LOG");
  return NULL;
}

/*
===========================================================================
..t2_main():::ENTER
only called after shared_log is initializes
::shared_log != null
consts not changed
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
args is always null
args == null
===========================================================================
..t2_main():::EXIT
consts not modified
::.str == orig(::.str)
::.str1 == orig(::.str1)
::.str2 == orig(::.str2)
always returns NULL
return == orig(args)
::shared_log != null
const strings are never modified
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
always returns NULL
return == null
*/
void *t2_main(void *args) {
  shared_log = malloc(sizeof(log_type));
  return NULL;
}

/*
 *
===========================================================================
..main():::ENTER
shared_log is statically initialized to 0
::shared_log == null
string constants are not modified
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
We always call the program with no arguments
argc == 1
argv is never null (ever?)
argv != null
===========================================================================
..main():::EXIT
String constants are not modified by main (or anyone)
::.str == orig(::.str)
::.str1 == orig(::.str1)
::.str2 == orig(::.str2)
shared log is initialzed in the program: in all runs, malloc succeeds and
returns non-null
::shared_log != null
::.str has only one value
::.str != null
::.str1 has only one value
::.str1 != null
::.str2 has only one value
::.str2 != null
main always returns 0
return == 0
 * 
 */
int main(int argc, char *argv[]) {
  pthread_mutex_init(&mem_lock, NULL);
  shared_log = malloc(sizeof(log_type));
  printf("Shared log malloc()'d\n");
  init_log(shared_log);

  pthread_t *tids = malloc(sizeof(pthread_t) * 2);
  pthread_create(&tids[0], NULL, t1_main, NULL);
  pthread_create(&tids[1], NULL, t2_main, NULL);
  pthread_join(tids[0], NULL);
  pthread_join(tids[1], NULL);

  return 0;
}

