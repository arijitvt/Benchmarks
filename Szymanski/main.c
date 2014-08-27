
/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>

#define LOOP_COUNT 5

int flag1 = 0, flag2 = 0; // integer flags 
int x; // boolean variable to test mutual exclusion

/*
 *
===========================================================================
..thr1():::ENTER
True: thread 1 starts so gets init
::flag1 == ::flag2
True: thread 1 starts so gets init
::flag1 == ::x
True: thread 1 starts so gets init
::flag1 == 0
===========================================================================
..thr1():::EXIT
True: either break out early or increase
::flag1 >= 0
True: either break out early or increase
::flag2 >= 0
True: thread 2 can interfere
::x one of { 0, 1 }
::flag1 >= ::x
::flag1 >= orig(::flag1)
::flag2 >= ::x
::flag2 >= orig(::flag1)
::x >= orig(::flag1)
*/
void *thr1() {
  flag1 = 1;
  int loopCounter  = LOOP_COUNT;
  while (flag2 >= 3) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
  }
  flag1 = 3;
  if (flag2 == 1) {
    flag1 = 2;
    loopCounter = LOOP_COUNT;
    while (flag2 != 4) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
    }
  }
  flag1 = 4;
  loopCounter = LOOP_COUNT;
  while (flag2 >= 2) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
  }
  // begin critical section
  x = 0;
  assert(1);
  // end critical section
  loopCounter = LOOP_COUNT ;
  while (2 <= flag2 && flag2 <= 3) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
  }
  flag1 = 0;
}

/*
 *
===========================================================================
..thr2():::ENTER
::flag2 == ::x
True: Thread 1 could have modified flag1
::flag1 >= 0
True: only thread 2 touches flag2
::flag2 == 0
::flag1 >= ::flag2
===========================================================================
..thr2():::EXIT
True: flag is only ever increased from 0
::flag1 >= 0
True: flag is only ever increased from 0
::flag2 >= 0
True: thread 1 can interfere
::x one of { 0, 1 }
::flag1 >= orig(::flag2)
::flag2 != ::x
::flag2 >= orig(::flag2)
::x >= orig(::flag2)
*/
void *thr2() {	
  flag2 = 1;
  int loopCounter = LOOP_COUNT;
  while (flag1 >= 3) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
  }
  flag2 = 3;
  if (flag1 == 1) {
    flag2 = 2;
    loopCounter = LOOP_COUNT;
    while (flag1 != 4) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
    }
  }
  flag2 = 4;
  loopCounter = LOOP_COUNT;
  while (flag1 >= 2) {
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
  }
  // begin critical section
  x = 1;
  assert(1);
  // end critical section
  
  loopCounter = LOOP_COUNT;
  while (2 <= flag1 && flag1 <= 3){
  	--loopCounter;
	if(loopCounter <= 0) {
		return 0;
	}
  }
  flag2 = 0;
}

/*
 *
===========================================================================
..main():::ENTER
True:const
::flag1 == ::flag2
::flag1 == ::x
::flag1 == 0
===========================================================================
..main():::EXIT
True:const
return == orig(::flag1)
return == orig(::flag2)
return == orig(::x)
Flags are always increased or unmodified
::flag1 >= 0
::flag2 >= 0
Thread {1,2} sets to {0,1}
::x one of { 0, 1 }
True:const
return == 0
::flag1 >= return
::flag2 >= return
::x >= return
*/
int main() {
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
/*
 * Daikon output
 * Num Inv: 30
 * Num true: 5
 * Num false: 25
 *
===========================================================================
..main():::ENTER
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == ::flag2
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == ::x
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == 0
===========================================================================
..main():::EXIT
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == ::flag2
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == return
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::flag1)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::flag2)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::x)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == 0
False: can be 0 or 1
::x == 1
===========================================================================
..thr1():::ENTER
True: both are zero on thread 1 entry
::flag1 == ::flag2
True: both are zero on thread 1 entry
::flag1 == ::x
True: both are zero on thread 1 entry
::flag1 == 0
===========================================================================
..thr1():::EXIT
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == ::flag2
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == ::x
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::flag1)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::flag2)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::x)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == 0
True: const
return == null
===========================================================================
..thr2():::ENTER
False: flag 1 could be modified by thread 1
::flag1 == ::flag2
False: flag 1 could be modified by thread 1
::flag1 == ::x
False: flag 1 could be modified by thread 1
::flag1 == 0
===========================================================================
..thr2():::EXIT
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == ::flag2
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::flag1)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::flag2)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == orig(::x)
False: they can be different if the threads reach different points (ie one breaks out early one doesnt)
::flag1 == 0
False: 0 or 1
::x == 1
True: const
return == null
 */
