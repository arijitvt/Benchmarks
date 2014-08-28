#include <pthread.h>
#include <assert.h>

pthread_mutex_t  mutex;
int data = 0;

/*
===========================================================================
..thread1():::ENTER
True: sees main's init
::data == 0
const
arg == null
===========================================================================
..thread1():::EXIT
return == orig(arg)
true could be modified by thread 2 or not
::data one of { 1, 3 }
const
return == null
incrementing
::data > orig(::data)
*/
void *thread1(void *arg)
{
  pthread_mutex_lock(&mutex);
  data++;
  pthread_mutex_unlock(&mutex);
  return NULL;
}


/*
===========================================================================
..thread2():::ENTER
true could be modified by thread 1 or not
::data one of { 0, 1 }
const
arg == null
===========================================================================
..thread2():::EXIT
return == orig(arg)
true could be modified by thread 1 or not
::data one of { 2, 3 }
const
return == null
::data > orig(::data)
 */
void *thread2(void *arg)
{
  pthread_mutex_lock(&mutex);
  data+=2;
  pthread_mutex_unlock(&mutex);
  return NULL;
}


/*
 *
===========================================================================
..thread3():::ENTER
True: incrmeented or not incremented by other threads
::data >= 0
const
arg == null
===========================================================================
..thread3():::EXIT
return == orig(arg)
True: incrmeented or not incremented by other threads
::data >= 0
return == null
::data >= orig(::data)
 */
void *thread3(void *arg)
{
  pthread_mutex_lock(&mutex);
  if (data >= 3){
#if 0
    ERROR: goto ERROR;
    ;
#endif
    assert(1);
  }
  pthread_mutex_unlock(&mutex);    
  return NULL;
}


/*
===========================================================================
..main():::ENTER
True: init
::data == 0
===========================================================================
..main():::EXIT
const
return == orig(::data)
Data = 1 + 2
::data == 3
const
return == 0
*/
int main()
{
  pthread_mutex_init(&mutex, 0);

  pthread_t t1, t2, t3;

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  pthread_create(&t3, 0, thread3, 0);

  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_join(t3, 0);
  
  return 0;
}

/*
 * Daikon Output
 * Num inv: 20
 * Num True: 13
 * Num False: 7
 *
===========================================================================
..main():::ENTER
True: init
::data == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::data)
True: data = 2 + 1
::data == 3
True: const
return == 0
===========================================================================
..thread1():::ENTER
False: should be 1
::data == 2
True: const
arg == null
===========================================================================
..thread1():::EXIT
True: const
return == orig(arg)
False: could be 2 or 3
::data == 3
True: const
return == null
===========================================================================
..thread2():::ENTER
False: could be 1 or 0
::data == 0
True: const
arg == null
===========================================================================
..thread2():::EXIT
True: const
return == orig(arg)
False: could be 2 or 3
::data == 2
True: const
return == null
===========================================================================
..thread3():::ENTER
False: could be 0,1,2,or, 3
::data == 3
True: const
arg == null
===========================================================================
..thread3():::EXIT
False: could be modified
::data == orig(::data)
True: const
return == orig(arg)
False: 
::data == 3
True: const
return == null
 */
