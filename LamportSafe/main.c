/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;

#define BIG 5

int x, y;
int b1, b2; // boolean flags
int X; // boolean variable to test mutual exclusion

/*
 *
===========================================================================
..thr1():::ENTER
True: t1 starts first and see main's init
::b1 == ::x
True: t1 starts first and see main's init
::b1 == ::y
True: t1 starts first and see main's init
::b1 == ::b2
True: t1 starts first and see main's init
::b1 == ::X
True: t1 starts first and see main's init
::b1 == 0
===========================================================================
..thr1():::EXIT
True: b1 is always set to zero
::b1 == orig(::b1)
True: b1 is always set to zero
::b1 == orig(::x)
True: b1 is always set to zero
::b1 == orig(::y)
True: b1 is always set to zero
::b1 == orig(::b2)
True: b1 is always set to zero
::b1 == orig(::X)
True: b1 is always set to zero
::b1 == 0
True: x,y, and X can see interference between threads
::x one of { 1, 2 }
::y one of { 0, 1, 2 }
::b2 one of { 0, 1 }
::X one of { 0, 1 }
True: const
return == null
::b1 < ::x
::b1 <= ::y
::b1 <= ::b2
::b1 <= ::X
::x >= ::b2
::x > ::X
::y >= ::X
::b2 >= ::X
*/
void *thr1() {
	int count1=BIG;
	int count2=BIG;
	int count3=BIG;
	int count4=BIG;
	while (1) {
		if(count1--<=0) {
			return NULL;
		}
		b1 = 1;
		x = 1;
		if (y != 0) {
			b1 = 0;
			while (y != 0) {
				if (count2--<=0) {
					return NULL;
				}
			}
			continue;
		}
		y = 1;
		if (x != 1) {
			b1 = 0;
			while (b2 >= 1) {
				if(count3--<=0) {
					return NULL;
				}
			}
			if (y != 1) {                        
				while (y != 0) {
					if(count4--<=0) {
						return NULL;
					}
				}
				continue;
			}
		}
		break;
	}
	// begin: critical section
	X = 0;
	//assert(X <= 0);
	// end: critical section
	y = 0;
	b1 = 0;
	return NULL;
}

/*
===========================================================================
..thr2():::ENTER
X can only ever be (1) only initialzied (set to zero) or (2) set to zero by
thread 1. So it is always zero
::b2 == ::X
True: thread1 can either be running or done
::b1 one of { 0, 1 }
True: x, y, could have been set or not by T1
::x one of { 0, 1 }
::y one of { 0, 1 }
::b2 == 0
::b1 >= ::y
::b1 >= ::b2
::x >= ::y
::x >= ::b2
::y >= ::b2
===========================================================================
..thr2():::EXIT
True: b2 is always set to zero
::b2 == orig(::b2)
True: b2 is always set to zero
::b2 == orig(::X)
True: t1 could be running
::b1 one of { 0, 1 }
True: see above
::x one of { 1, 2 }
True: see above
::y one of { 0, 1, 2 }
True: see above
::b2 == 0
True: see above
::X one of { 0, 1 }
True: const
return == null
::b1 <= ::x
::b1 >= ::b2
::x > ::b2
::x >= ::X
::x >= orig(::b1)
::x >= orig(::x)
::x > orig(::y)
::y >= ::b2
::b2 <= ::X
::b2 <= orig(::b1)
::b2 <= orig(::x)
::b2 <= orig(::y)
*/
void *thr2() {
	int count1=BIG;
	int count2=BIG;
	int count3=BIG;
	int count4=BIG;
	while (1) {
		if(count1--<=0) {
			return NULL;
		}
		b2 = 1;
		x = 2;
		if (y != 0) {
			b2 = 0;
			while (y != 0) {
				if (count2--<=0) {
					return NULL;
				}
			}
			continue;
		}
		y = 2;
		if (x != 2) {
			b2 = 0;
			while (b1 >= 1) {
				if(count3--<=0){
					return NULL;
				}
			}

			if (y != 2) {
				while (y != 0) {
					if(count4--<=0) {
						return NULL;
					}
				}
				continue;
			}
		}
		break;
	}
	// begin: critical section
	X = 1;
	//assert(X >= 1);
	// end: critical section
	y = 0;
	b2 = 0;
	return NULL;
}

/*
 *
===========================================================================
..main():::ENTER
True: init
::b1 == ::x
True: init
::b1 == ::y
True: init
::b1 == ::b2
True: init
::b1 == ::X
True: init
::b1 == 0
===========================================================================
..main():::EXIT
True: on exit, both threads always set their flag to zero
::b1 == ::b2
True: on exit, both threads always set their flag to zero
::b1 == return
True: on exit, both threads always set their flag to zero
::b1 == orig(::b1)
True: on exit, both threads always set their flag to zero
::b1 == orig(::x)
True: on exit, both threads always set their flag to zero
::b1 == orig(::y)
True: on exit, both threads always set their flag to zero
::b1 == orig(::b2)
True: on exit, both threads always set their flag to zero
::b1 == orig(::X)
True: on exit, both threads always set their flag to zero
::b1 == 0
True: thread 1 sets to 1 thread 2 sets to 2
::x one of { 1, 2 }
True: thread 1 sets to 0 or 1 and thread to sets to 0 or 2
::y one of { 0, 1, 2 }
True: thread either sets to 0 or 1
::X one of { 0, 1 }
::b1 < ::x
::b1 <= ::y
::b1 <= ::X
::x != ::y
::x >= ::X
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
 * Daikon Output
 * Num Inv: 48
 * Num True: 12
 * Num False: 36
 *
 *
..main():::ENTER
True: init
::x == ::y
True: init
::x == ::b1
True: init
::x == ::b2
True: init
::x == ::X
True: init
::x == 0
===========================================================================
..main():::EXIT
False:
::y == ::b1
False:
::y == ::b2
False:
::y == return
False:
::y == orig(::x)
False:
::y == orig(::y)
False:
::y == orig(::b1)
False:
::y == orig(::b2)
False:
::y == orig(::X)
False:
::x == 2
False:
::y == 0
False:
::X == 1
===========================================================================
..thr1():::ENTER
True: set by main
::x == ::y
True: set by main
::x == ::b1
True: set by main
::x == ::b2
True: set by main
::x == ::X
True: set by main
::x == 0
===========================================================================
..thr1():::EXIT
False:
::y == ::b1
False:
::y == ::b2
False:
::y == ::X
False:
::y == orig(::x)
False:
::y == orig(::y)
False:
::y == orig(::b1)
False:
::y == orig(::b2)
False:
::y == orig(::X)
False:
::x == 1
False:
::y == 0
True: const
return == null
===========================================================================
..thr2():::ENTER
False:
::y == ::b1
False:
::y == ::b2
False:
::y == ::X
False:
::x == 1
False:
::y == 0
===========================================================================
..thr2():::EXIT
False: can be many things! see above
::y == ::b1
False: can be many things! see above
::y == ::b2
False: can be many things! see above
::y == orig(::y)
False: can be many things! see above
::y == orig(::b1)
False: can be many things! see above
::y == orig(::b2)
False: can be many things! see above
::y == orig(::X)
False: can be many things! see above
::X == orig(::x)
False: can be many things! see above
::x == 2
False: can be many things! see above
::y == 0
False: can be 0 or 1
::X == 1
True: const
return == null
*/
