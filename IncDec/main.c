
#include <pthread.h>


volatile unsigned value = 0, m = 0;

/*
 * ==== Thread 1 Invariants ====
===========================================================================
..__VERIFIER_atomic_acquire():::ENTER
True: if thread 2 acquires first (ie, enter's first), then it will not modify
`value`, `dec_v`, or `dec_flag` because value is zero.
::value == ::inc_flag
::value == ::dec_flag
::value == ::inc_v
::value == ::dec_v
::value == 0
True: thread 2 can enter acquire() before or after thread 1 does
::m one of { 0, 1 }
::value <= ::m
===========================================================================
..__VERIFIER_atomic_acquire():::EXIT
True: if thread 2 acquires first (ie, enter's first), then it will not modify
`value`, `dec_v`, or `dec_flag` because value is zero.
::value == ::inc_flag
::value == ::dec_flag
::value == ::inc_v
::value == ::dec_v
::value == orig(::value)
::value == orig(::inc_flag)
::value == orig(::dec_flag)
::value == orig(::inc_v)
::value == orig(::dec_v)
::value == 0
True: m is always one upon leaving this (silly) lock
::m == 1
::value <= orig(::m)
::m >= orig(::m)
 * ==== End Thread 1 Invariants ====
 *
 * ==== Thread 2 Invariants ====
===========================================================================
..__VERIFIER_atomic_acquire():::ENTER
True: Thread 2 cannot decrement if  it does not acqure first
::dec_flag == ::inc_v
True: Thread 2 cannot decrement if  it does not acqure first
::dec_flag == ::dec_v
True: Thread 1 could modify value before thread 2 acquires
::value one of { 0, 1 }
True: thread 2 can enter acquire() before or after thread 2 does
::m one of { 0, 1 }
True: Thread 1 could modify value before thread 2 acquires
::inc_flag one of { 0, 1 }
True: Thread 2 cannot decrement if  it does not acqure first
::dec_flag == 0
::value <= ::inc_flag
::value >= ::dec_flag
::m <= ::inc_flag
::m >= ::dec_flag
True: thread 2 cannot decrment if thread 1 does not increment
::inc_flag >= ::dec_flag
===========================================================================
..__VERIFIER_atomic_acquire():::EXIT
True: if thread1 does not increment that dec_flag is zero
::dec_flag == ::inc_v
::dec_flag == ::dec_v
::dec_flag == orig(::dec_flag)
::dec_flag == orig(::inc_v)
::dec_flag == orig(::dec_v)
True: thread 1 can modify `value` during this function
::value one of { 0, 1 }
True: always set
::m == 1
True: thread 1 can modify `value` during this function
::inc_flag one of { 0, 1 }
True: thread 2 must call this function before decrementing
::dec_flag == 0
::value <= ::m
::value <= ::inc_flag
::value >= ::dec_flag
::value >= orig(::value)
::m >= ::inc_flag
::m >= orig(::value)
::m >= orig(::m)
::m >= orig(::inc_flag)
True: thread 2 cannot decrment if thread 1 does not increment
::inc_flag >= ::dec_flag
::inc_flag >= orig(::value)
::inc_flag >= orig(::m)
::inc_flag >= orig(::inc_flag)
::dec_flag <= orig(::value)
::dec_flag <= orig(::m)
::dec_flag <= orig(::inc_flag)
*/
void __VERIFIER_atomic_acquire()
{
	if(m == 0 ) {
		m = 1;
	}
}

/*
 * ==== Thread 1 Invariants ====
===========================================================================
..__VERIFIER_atomic_release():::ENTER
::m == ::inc_flag
::dec_flag == ::dec_v
True: Value can either be 0 or 1 for thread 1 depending on if the dec() thread
decrements before or after the inc() thread reqleases (note: the lock isn't
actually doing anything!)
::value one of { 0, 1 }
True: m is always 1 before release
::m == 1
True: see above comment on value
::dec_flag one of { 0, 1 }
True: value is only incremented from zero
::inc_v == 0
::value <= ::m
::value != ::dec_flag
::value >= ::inc_v
::m >= ::dec_flag
::dec_flag >= ::inc_v
===========================================================================
..__VERIFIER_atomic_release():::EXIT
True: at exit m is always zero
::m == ::inc_v
True: value is only incremented from zero
::m == orig(::inc_v)
True: inc_flag is always one when this is called (the increment always occurrs, value is never negative)
::inc_flag == orig(::m)
::inc_flag == orig(::inc_flag)
True: see comments above main()
::dec_flag == ::dec_v
True: increment always ocurrs
::value one of { 0, 1 }
True: always zero on release
::m == 0
True: increment always happens
::inc_flag == 1
True: decrement sometimes happens
::dec_flag one of { 0, 1 }
::value >= ::m
::value <= ::inc_flag
::value != ::dec_flag
::value <= orig(::value)
::m <= ::dec_flag
::m <= orig(::value)
::m <= orig(::dec_flag)
::inc_flag >= ::dec_flag
::inc_flag >= orig(::value)
::inc_flag >= orig(::dec_flag)
::dec_flag >= orig(::dec_flag)
===========================================================================
* ==== End Thread 1 Invariants ====
*
* ==== Thread 2 Invariants ====
===========================================================================
..__VERIFIER_atomic_release():::ENTER
True: see comment above main()
::dec_flag == ::dec_v
True: increment always happens
::value one of { 0, 1 }
True: thread 1 could release before thread 2
::m one of { 0, 1 }
True: thread 2 calls release if inc_flag is zero
::inc_flag one of { 0, 1 }
True: thread 2 calls release if inc_flag is zero implying dec_flag did not get
set to 1
::dec_flag one of { 0, 1 }
True: inc_v is always zero
::inc_v == 0
::value <= ::inc_flag
::value >= ::inc_v
::m >= ::inc_v
::inc_flag >= ::dec_flag
::inc_flag >= ::inc_v
::dec_flag >= ::inc_v
===========================================================================
..__VERIFIER_atomic_release():::EXIT
True: m is always zero after release
::m == ::inc_v
::m == orig(::inc_v)
True: see comment above main()
::dec_flag == ::dec_v
::dec_flag == orig(::dec_flag)
::dec_flag == orig(::dec_v)
True: increment always happens
::value one of { 0, 1 }
True: always 0 on release
::m == 0
True: see above
::inc_flag one of { 0, 1 }
::dec_flag one of { 0, 1 }
::value >= ::m
::value <= ::inc_flag
::value >= orig(::value)
::m <= ::inc_flag
::m <= ::dec_flag
::m <= orig(::value)
::m <= orig(::m)
::m <= orig(::inc_flag)
::inc_flag >= ::dec_flag
::inc_flag >= orig(::value)
::inc_flag >= orig(::inc_flag)
::dec_flag <= orig(::inc_flag)
===========================================================================
*
*/
void __VERIFIER_atomic_release()
{
	if(m == 1) {
		m = 0;
	}
}

/*helpers for the property*/
volatile unsigned inc_flag = 0;
volatile unsigned dec_flag = 0;
unsigned inc_v = 0;
unsigned dec_v = 0 ;

/*
===========================================================================
..inc():::ENTER
True: value is always zero when inc() starts (inc thread starts first)
::value == ::inc_flag
::value == ::dec_flag
::value == ::inc_v
::value == ::dec_v
::value == 0
::m one of { 0, 1 }
True: const
arg == null
::value <= ::m
===========================================================================
..inc():::EXIT
True: inc_v is always 0 and m is always released
::m == ::inc_v
::m == orig(::value)
::m == orig(::inc_flag)
::m == orig(::dec_flag)
::m == orig(::inc_v)
::m == orig(::dec_v)
True: see above main()
::dec_flag == ::dec_v
True: value is always incremented
::value one of { 0, 1 }
True: inc_v is always 0 and m is always released
::m == 0
True: value is always incremented
::inc_flag == 1
True: dec only sometimes
::dec_flag one of { 0, 1 }
return != null
::value >= ::m
::value <= ::inc_flag
::value != ::dec_flag
::value >= orig(::m)
::m <= ::dec_flag
::m <= orig(::m)
::inc_flag >= ::dec_flag
::inc_flag >= orig(::m)
*/
void* inc(void *arg) {

	__VERIFIER_atomic_acquire();
	if(value == 0u-1) {
		__VERIFIER_atomic_release();
	}else{
		inc_v = value;
		inc_flag = 1, value = inc_v + 1; /*set flag, then update*/
		__VERIFIER_atomic_release();
	}
}

/*
 *
===========================================================================
..dec():::ENTER
True: see comments above main()
::dec_flag == ::inc_v
::dec_flag == ::dec_v
True: value is always incremented
::value one of { 0, 1 }
True: m is sometimes acquired before this thread starts
::m one of { 0, 1 }
::inc_flag one of { 0, 1 }
True: sometimes decremented
::dec_flag == 0
True: const
arg == null
::value <= ::inc_flag
::value >= ::dec_flag
::m <= ::inc_flag
::m >= ::dec_flag
::inc_flag >= ::dec_flag
===========================================================================
..dec():::EXIT
True: m is always zero on end
::m == ::inc_v
::m == orig(::dec_flag)
::m == orig(::inc_v)
::m == orig(::dec_v)
::dec_flag == ::dec_v
::value one of { 0, 1 }
::m == 0
::inc_flag one of { 0, 1 }
::dec_flag one of { 0, 1 }
True: const
return != null
::value >= ::m
::value <= ::inc_flag
::m <= ::inc_flag
::m <= ::dec_flag
::m <= orig(::value)
::m <= orig(::m)
::m <= orig(::inc_flag)
::inc_flag >= ::dec_flag
::inc_flag >= orig(::value)
::inc_flag >= orig(::m)
::inc_flag >= orig(::inc_flag)
::dec_flag >= orig(::value)
*/
void* dec(void *arg) {
	__VERIFIER_atomic_acquire();
	if(value == 0) {
		__VERIFIER_atomic_release();
	}else{
		dec_v = value;
		dec_flag = 1, value = dec_v - 1; /*set flag, then update*/
		__VERIFIER_atomic_release();
	}
}

/*
===========================================================================
..main():::ENTER
True: everything is statically initialized to zero
::value == ::m
::value == ::inc_flag
::value == ::dec_flag
::value == ::inc_v
::value == ::dec_v
::value == 0
===========================================================================
..main():::EXIT
True: m == inc_v == 0: all threads release the lock
::m == ::inc_v
True: m is zero
::m == return
True: m is zero
::m == orig(::value)
True: m is zero
::m == orig(::m)
True: m is zero
::m == orig(::inc_flag)
True: m is zero
::m == orig(::dec_flag)
True: m is zero
::m == orig(::inc_v)
True: m is zero
::m == orig(::dec_v)
True: If dec_flag is one, then value != 0 and dec_v is set to value so dec_v != 0
(else branch of dec()). Value can only be one in this case. If dec_flag is zero
this means it was never set meaning dec_v is also never set so they stay at
their initialized values of zero
::dec_flag == ::dec_v
True: See above
::value one of { 0, 1 }
True: 
::m == 0
True: Value can never be negative (it is only decremented if it is non-zero) meaning
it is always incremented (i.e., the if branch of inc() is never hit)
::inc_flag == 1
True: The decrement operation can be skipped if it occurs before the increment operation
::dec_flag one of { 0, 1 }
::value >= ::m
::value <= ::inc_flag
::value != ::dec_flag
::m <= ::dec_flag
::inc_flag >= ::dec_flag
*/
int main(){
	pthread_t inc_thr,dec_thr;
	pthread_create(&inc_thr,0,inc,0);
	pthread_create(&dec_thr,0,dec,0);
	pthread_join(inc_thr,0);
	pthread_join(dec_thr,0);
	return 0;
}

/*
 * Example Daikon Output
 *
 * Num invariants: 94
 * Num true: 37
 * Num false: 57
===========================================================================
..__VERIFIER_atomic_acquire():::ENTER
False: m could be either 1 or 0 depending on if another thread acquired the lock already
::value == ::m
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::inc_flag
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::dec_flag
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::inc_v
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::dec_v
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == 0
===========================================================================
..__VERIFIER_atomic_acquire():::EXIT
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::inc_flag
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::dec_flag
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::inc_v
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == ::dec_v
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == orig(::value)
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == orig(::m)
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == orig(::inc_flag)
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == orig(::dec_flag)
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == orig(::inc_v)
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == orig(::dec_v)
False: Value can be either 0 or 1 when a thread enters acquire since the other thread could have performed a modification
::value == 0
1. True: m is always set to one on exit
::m == 1
===========================================================================
..__VERIFIER_atomic_release():::ENTER
::value == ::inc_flag
False: decrement is only sometimes performed
::dec_flag == ::inc_v
2. True: dec_flag always mirrors dec_v
::dec_flag == ::dec_v
3. True: value is either incremented or decrmented
::value one of { 0, 1 }
False: another thread could have modified the mutex
::m == 1
False: dec_flag is sometimes 1
::dec_flag == 0
===========================================================================
..__VERIFIER_atomic_release():::EXIT
False: value can be zero or one
::value == ::inc_flag
False: value can change in this function
::value == orig(::value)
False: value can be zero or one
::value == orig(::inc_flag)
False: dec flag can be zero or one
::m == ::dec_flag
4. True: inc_v is always 0
::m == ::inc_v
False: dec_v is sometimes 1
::m == ::dec_v
False: dec_flag can change in this function
::m == orig(::dec_flag)
False: inc_v can change in this function
::m == orig(::inc_v)
False: dec_v can change in this function
::m == orig(::dec_v)
5. True: value could be either zero or one
::value one of { 0, 1 }
6. True: m is always released
::m == 0
===========================================================================
..dec():::ENTER
False: value can be one
::value == ::m
False: value can be one
::value == ::inc_flag
False: value can be one
::value == ::dec_flag
False: value can be one
::value == ::inc_v
False: value can be one
::value == ::dec_v
False: value can be one
::value == 0
7. True: const
arg == null
===========================================================================
..dec():::EXIT
False: value can be zero or one
::value == ::m
False: value can be zero or one
::value == ::inc_flag
False: value can be zero or one
::value == ::dec_flag
False: value can be zero or one
::value == ::inc_v
False: value can be zero or one
::value == ::dec_v
False: value can be zero or one
::value == orig(::value)
False: value can be zero or one
::value == orig(::m)
False: value can be zero or one
::value == orig(::inc_flag)
False: value can be zero or one
::value == orig(::dec_flag)
False: value can be zero or one
::value == orig(::inc_v)
False: value can be zero or one
::value == orig(::dec_v)
False: value can be zero or one
::value == 0
8. True: const
return has only one value
===========================================================================
..inc():::ENTER
False: m can be zero or one
::value == ::m
9. True: value is zero on entry
::value == ::inc_flag
10. True: value is zero on entry
::value == ::dec_flag
11. True: value is zero on entry
::value == ::inc_v
12. True: value is zero on entry
::value == ::dec_v
13. True: value is zero on entry
::value == 0
14. True: const
arg == null
===========================================================================
..inc():::EXIT
::value == ::inc_flag
False: dec_flag can be zero or one
::m == ::dec_flag
15. True: inc_v is always zoer
::m == ::inc_v
False: dec_ can be zero or one
::m == ::dec_v
16. True: == 0
::m == orig(::value)
False: m could be one on entry
::m == orig(::m)
17. True: inc_flag == 0
::m == orig(::inc_flag)
18. True: dec_flag == 0 on entry
::m == orig(::dec_flag)
19. True:
::m == orig(::inc_v)
20. True:
::m == orig(::dec_v)
False: value can be zero or one
::value == 1
21. True: m is always released
::m == 0
22. True: const
return has only one value
===========================================================================
..main():::ENTER
23. True: init
::value == ::m
24. True: init
::value == ::inc_flag
25. True: init
::value == ::dec_flag
26. True: init
::value == ::inc_v
27. True: init
::value == ::dec_v
28. True: init
::value == 0
===========================================================================
..main():::EXIT
False: zero or one
::value == ::inc_flag
False: flag 0 or 1
::m == ::dec_flag
29. True: inc_v == 0
::m == ::inc_v
False: dec_v = 0 or 1
::m == ::dec_v
30. True:
::m == orig(::value)
31. True:
::m == orig(::m)
32. True:
::m == orig(::inc_flag)
33. True:
::m == orig(::dec_flag)
34. True:
::m == orig(::inc_v)
35. True:
::m == orig(::dec_v)
False: 0 or 1
::value == 1
36. True: always released
::m == 0
37. True: const
return == 0
 */
