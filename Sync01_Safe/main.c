#include <stdio.h> 
#include <pthread.h>
#include <assert.h>

int  num;

pthread_mutex_t  m;
pthread_cond_t  empty, full;

/*
===========================================================================
..thread1():::ENTER
True: sees main's init
::num == 1
True: const
arg == null
===========================================================================
..thread1():::EXIT
True: num is dec'ed by thread 2 then inc'ed by this thread
::num == orig(::num)
True: num is dec'ed by thread 2 then inc'ed by this thread
::num == 1
*/
void * thread1(void * arg)
{
  pthread_mutex_lock(&m);

  while (num > 0) 
    pthread_cond_wait(&empty, &m);
  
  num++;

  pthread_mutex_unlock(&m);
  pthread_cond_signal(&full);
  return NULL;
}


/*
===========================================================================
..thread2():::ENTER
True: number is modified by this thread to be set to 0. Until this happens,
thread 1 must wait to set it back to 1. So num must always be 1.
::num == 1
True: const
arg == null
===========================================================================
..thread2():::EXIT
True: either this thread finishes before or after thread1 inc's num.
::num one of { 0, 1 }
*/
void * thread2(void * arg)
{
  pthread_mutex_lock(&m);

  while (num == 0) 
    pthread_cond_wait(&full, &m);

  num--;
  
  pthread_mutex_unlock(&m);

  pthread_cond_signal(&empty);
  return NULL;
}


/*
===========================================================================
..main():::ENTER
True: init
::num == 0
===========================================================================
..main():::EXIT
return == orig(::num)
num always ends at its original value (there is one dec and one inc). Num is
initialized to 1 (by main).
::num == 1
True: const 
return == 0
*/
int main()
{
  pthread_t  t1, t2;

  num = 1;

  pthread_mutex_init(&m, 0);
  pthread_cond_init(&empty, 0);
  pthread_cond_init(&full, 0);
  
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  if (num!=1)
  {
    //ERROR: goto ERROR;
    //;
   // assert(0);
  }

  return 0;
  
}

/*
 * Daikon Output:
 * Num Inv: 15
 * Num false: 1
 * Num true: 14
 *
===========================================================================
..main():::ENTER
True: init
::num == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::num)
True: always 1
::num == 1
True: const
return == 0
===========================================================================
..thread1():::ENTER
True: see's main's init
::num == 1
True: const
arg == null
===========================================================================
..thread1():::EXIT
True: always set back to 1 by this thread
::num == orig(::num)
True: const
return == orig(arg)
True: always set back to 1 by this thread
::num == 1
True: const
return == null
===========================================================================
..thread2():::ENTER
True: must be 1
::num == 1
True: const
arg == null
===========================================================================
..thread2():::EXIT
True: const
return == orig(arg)
False: could be 1 or 0
::num == 0
True: const
return == null
 */
