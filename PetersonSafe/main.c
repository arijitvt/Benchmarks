/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;

#define IT 10

int flag1 = 0, flag2 = 0; // boolean flags
int turn; // integer variable to hold the ID of the thread whose turn is it
int x; // boolean variable to test mutual exclusion

/*
===========================================================================
..thr1():::ENTER
True: T1 goes first so sees main's init
::flag1 == ::flag2
True: T1 goes first so sees main's init
::flag1 == ::turn
True: T1 goes first so sees main's init
::flag1 == ::x
True: T1 goes first so sees main's init
::flag1 == 0
===========================================================================
..thr1():::EXIT
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::x == orig(::flag1)
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::x == orig(::flag2)
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::x == orig(::turn)
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::x == orig(::x)
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::flag1 one of { 0, 1 }
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::flag2 one of { 0, 1 }
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::turn one of { 0, 1 }
True: If T1 fails then X stays at zero; if T1 suceeds then X becomes 0
::x == 0
True: const
return == null
::flag1 <= ::flag2
::flag1 <= ::turn
::flag1 >= ::x
::flag2 >= ::x
::turn >= ::x
*/
void *thr1() {
    int count=0;
  flag1 = 1;
  turn = 1;

  while (flag2==1 && turn==1) {
      if (count++ > IT) return NULL;
  }

  // begin: critical section
  x = 0;
  //assert(x<=0);
  // end: critical section
  flag1 = 0;
  return NULL;
}

/*
 *
===========================================================================
..thr2():::ENTER
True: flag 2 is always zero at the start (same with X, it is only set by this
thread)
::flag2 == ::x
True: set or not by t1
::flag1 one of { 0, 1 }
True: only set by this thread
::flag2 == 0
True: set or not by t1
::turn one of { 0, 1 }
::flag1 >= ::flag2
::flag2 <= ::turn
===========================================================================
..thr2():::EXIT
True: set or not by t1
::flag1 one of { 0, 1 }
True: set or not by t1
::flag2 one of { 0, 1 }
True: set or not by t1
::turn one of { 0, 1 }
True: either we suceed or fail
::x one of { 0, 1 }
True: const
return == null
::flag1 >= ::turn
::flag1 >= orig(::flag2)
::flag2 != ::x
::flag2 >= orig(::flag2)
::turn <= ::x
::turn >= orig(::flag2)
::x >= orig(::flag2)
*/
void *thr2() {
    int count=0;
  flag2 = 1;
  turn = 0;
  while (flag1==1 && turn==0) { 
	if(count++ >IT) return NULL;
  }
  // begin: critical section
  x = 1;
  //assert(x>=1);
  // end: critical section
  flag2 = 0;
  return NULL;
}

/*
 *
===========================================================================
..main():::ENTER
True: init
::flag1 == ::flag2
True: init
::flag1 == ::turn
True: init
::flag1 == ::x
True: init
::flag1 == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::flag1)
True: const
return == orig(::flag2)
True: const
return == orig(::turn)
True: const
return == orig(::x)
True: thread 1 either fails or suceeds
::flag1 one of { 0, 1 }
True: thread 2 either fails or suceeds
::flag2 one of { 0, 1 }
True: thread 1/2 either fails or suceeds
::turn one of { 0, 1 }
True: thread 1/2 either fails or suceeds
::x one of { 0, 1 }
True: const
return == 0
::flag1 >= return
::flag2 >= return
::turn >= return
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
 * Daikon Output:
 * Num Inv: 39
 * Num True: 10
 * Num False: 29
 *
===========================================================================
..main():::ENTER
True: init
::flag1 == ::flag2
True: init
::flag1 == ::turn
True: init
::flag1 == ::x
True: init
::flag1 == 0
===========================================================================
..main():::EXIT
False: they can be different
::flag1 == ::flag2
False: they can be different
::flag1 == ::turn
False: they can be different
::flag1 == return
False: it can be modified
::flag1 == orig(::flag1)
False: it can be modified
::flag1 == orig(::flag2)
False: it can be modified
::flag1 == orig(::turn)
False: it can be modified
::flag1 == orig(::x)
False: it can be modified
::flag1 == 0
False: can be zero or 1
::x == 1
===========================================================================
..thr1():::ENTER
True: t1 see's main's init
::flag1 == ::flag2
True: t1 see's main's init
::flag1 == ::turn
True: t1 see's main's init
::flag1 == ::x
True: t1 see's main's init
::flag1 == 0
===========================================================================
..thr1():::EXIT
False: can be different
::flag1 == ::flag2
False: can be different
::flag1 == ::x
False: can be different
::flag1 == orig(::flag1)
False: can be different
::flag1 == orig(::flag2)
False: can be different
::flag1 == orig(::turn)
False: can be different
::flag1 == orig(::x)
False: can be different
::flag1 == 0
False: can be different
::turn == 1
True: const
return == null
===========================================================================
..thr2():::ENTER
False: can be modified
::flag1 == ::flag2
False: can be modified
::flag1 == ::x
False: can be modified
::flag1 == 0
False: can be modified
::turn == 1
===========================================================================
..thr2():::EXIT
False: they can be different
::flag1 == ::flag2
False: they can be different
::flag1 == ::turn
False: they can be different
::flag1 == orig(::flag1)
False: they can be different
::flag1 == orig(::flag2)
False: they can be different
::flag1 == orig(::x)
False: they can be different
::x == orig(::turn)
False: can be 1
::flag1 == 0
False: 0 or 1
::x == 1
True: const
return == null
*/
