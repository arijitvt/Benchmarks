#include <pthread.h> 
#include <assert.h>

pthread_mutex_t  ma, mb;
int data1, data2;

/*
===========================================================================
..thread1():::ENTER
True: see's main's init
::data1 == ::data2
True: see's main's init
::data1 == 10
True: const
arg == null
===========================================================================
..thread1():::EXIT
True: const
return == orig(arg)
True: thread 1 could have, or could not have, modified data1 or data2 at the
time of exit
::data1 one of { 11, 16 }
True: thread 1 could have, or could not have, modified data1 or data2 at the
time of exit
::data2 one of { 5, 11 }
True: const
return == null
::data1 >= ::data2
::data1 > orig(::data1)
::data2 != orig(::data1)
*/
void * thread1(void * arg)
{  
  pthread_mutex_lock(&ma);
  data1++;
  pthread_mutex_unlock(&ma);

  pthread_mutex_lock(&ma);
  data2++;
  pthread_mutex_unlock(&ma);
  return NULL;
}


/*
===========================================================================
..thread2():::ENTER
True: thread 1 could have or could not have performed its modification at start
time
::data1 one of { 10, 11 }
True: thread 1 could have or could not have performed its modification at start
time
::data2 one of { 10, 11 }
True: const
arg == null
::data1 >= ::data2
===========================================================================
..thread2():::EXIT
True: const
return == orig(arg)
True: thread 2 could have, or could not have, modified data1 or data2 at the
time of exit
::data1 one of { 15, 16 }
True: thread 2 could have, or could not have, modified data1 or data2 at the
time of exit
::data2 one of { 4, 5 }
True: const
return == null
::data1 > ::data2
::data1 > orig(::data1)
::data1 > orig(::data2)
::data2 < orig(::data1)
::data2 < orig(::data2)
*/
void * thread2(void * arg)
{  
  pthread_mutex_lock(&ma);
  data1+=5;
  pthread_mutex_unlock(&ma);

  pthread_mutex_lock(&ma);
  data2-=6;
  pthread_mutex_unlock(&ma);
  return NULL;
}


/*
 *
===========================================================================
..main():::ENTER
True: init
::data1 == ::data2
True: init
::data1 == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::data1)
True: const
return == orig(::data2)
True: data1 = 10 + 1 + 5 = 16
::data1 == 16
True: data2 = 10 - 6 + 1 = 5
::data2 == 5
True: const
return == 0
*/
int main()
{
  pthread_t  t1, t2;

  pthread_mutex_init(&ma, 0);
  pthread_mutex_init(&mb, 0);

  data1 = 10;
  data2 = 10;

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  if (data1!=16 && data2!=5)
  {
    assert(1);
  }

  return 0;
}

/*
 * DAikon OUtput: 
 * Num Inv: 21
 * Num false: 6
 * Num True: 15
 *
===========================================================================
..main():::ENTER
True: init
::data1 == ::data2
True: init
::data1 == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::data1)
True: const
return == orig(::data2)
True: see above
::data1 == 16
True: see above
::data2 == 5
True: const
return == 0
===========================================================================
..thread1():::ENTER
True: sees main's init
::data1 == ::data2
True: sees main's init
::data1 == 10
True: const
arg == null
===========================================================================
..thread1():::EXIT
False: could be modified by thread 2
::data1 == ::data2
True: const
return == orig(arg)
False: could be modified by thread 2
::data1 == 11
True: const
return == null
===========================================================================
..thread2():::ENTER
False: could be modified or not modified by thread 1
::data1 == ::data2
False: could be modified or not modified by thread 1
::data1 == 11
True: const
arg == null
===========================================================================
..thread2():::EXIT
True: const
return == orig(arg)
False: could be modified or not modified by thread 1
::data1 == 16
False: could be modified or not modified by thread 1
::data2 == 5
True: const
return == null
*/
