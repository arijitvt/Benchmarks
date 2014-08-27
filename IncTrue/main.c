
#include <pthread.h>

#define BIG 2

volatile unsigned value= 0;
volatile unsigned m = 0;

#define  __VERIFIER_atomic_acquire() \
{                              \
	if(m == 0) {            \
		m = 1;           \
	}                         \
}                                  \



#define __VERIFIER_atomic_release() \
{                                   \
	if(m == 1) {                \
		m = 0;              \
	}                           \
}                                   \


/*
 * ==== Thread 2 Invariants ====
 *
===========================================================================
..thr1():::ENTER
True: thread 1 goes first (init)
::value == ::m
True: thread 1 goes first (init)
::value == 0
True: const
arg == null
===========================================================================
..thr1():::EXIT
True: always released
::m == orig(::value)
True: always released
::m == orig(::m)
True: const
return == orig(arg)
True: 1 inc or 2
::value one of { 1, 2 }
True: always released
::m == 0
True: const
return == null
True: 1 inc or 2
::value > ::m
* =======
*
* ==== Thread 2 Inv ====
===========================================================================
..thr1():::ENTER
True: thread 1 goes firs
::value one of { 0, 1 }
::m one of { 0, 1 }
arg == null
===========================================================================
..thr1():::EXIT
return == orig(arg)
::value one of { 1, 2 }
::m == 0
return == null
::value > ::m
::value > orig(::value)
::value >= orig(::m)
::m <= orig(::value)
::m <= orig(::m)
*/
void * thr1(void* arg) {
	unsigned v = 0;

	__VERIFIER_atomic_acquire();
	if(value == 0u-1) {
		__VERIFIER_atomic_release();

		return 0;
	}else{

		v = value;
		value = v + 1;
		__VERIFIER_atomic_release();

		return 0;
	}
}

/*
 *
===========================================================================
..main():::ENTER
True: init
::value == ::m
True: init
::value == 0
===========================================================================
..main():::EXIT
True: always released
::m == return
True: always released
::m == orig(::value)
True: always released
::m == orig(::m)
True: Either one inc or two
::value one of { 1, 2 }
True: always released
::m == 0
True: Either one inc or two
::value > ::m
*/
int main(){
	pthread_t t[BIG];
	int i;
	for  (i = 0 ; i < BIG; ++i) {
		pthread_create(&t[i], 0, thr1, 0); 
	}
	for  (i = 0 ; i < BIG; ++i) {
		pthread_join(t[i], 0); 
	}
	return 0;
}

/*
 *
 * Daikon output
 * Num Inv: 15
 * Num true: 12
 * Num False: 3
 *
===========================================================================
True: init
..main():::ENTER
True: init
::value == ::m
True: init
::value == 0
===========================================================================
..main():::EXIT
True: released
::m == orig(::value)
True: released
::m == orig(::m)
False: 1 or 2 incs
::value == 2
True: released
::m == 0
True: const
return == 0
===========================================================================
..thr1():::ENTER
True: 1 inc or 2
::value one of { 0, 1 }
False: m can be one at the start
::m == 0
True: const
arg == null
===========================================================================
..thr1():::EXIT
False: m can be 1 at the start
::m == orig(::m)
True: const
return == orig(arg)
True: 1 inc or 2
::value one of { 1, 2 }
True: released
::m == 0
True: const
return == null
*/
