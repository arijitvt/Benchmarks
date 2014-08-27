/*
 * See the bottom of this file for an example daikon output
 */
#include <pthread.h>

#define LOOP_COUNT 5
#define THREAD_COUNT 2 

volatile unsigned value = 0;

/*helpers for the property*/
volatile unsigned inc_flag = 0;
volatile unsigned dec_flag = 0;


/*
 * ==== Thread 1 Invariants ====
===========================================================================
True both threads break out if the other completes a successful cas()
operation. This means that they will only call the cas() function if value is
still 0 and neither of the flags are true. 
::value == ::inc_flag
::value == ::dec_flag
True e is the expected value of value (which is always zero, see above)
::value == e
::value == 0
v has only one value
v != null
True Thread 1 is always incrementing the value from 0 to 1
u == 1
True
r != null
True, the threads stop calling this function when one of the flags are true
flag has only one value
True
flag != null
===========================================================================
..__VERIFIER_atomic_CAS():::EXIT
True: either decrement or increment suceeds
::value one of { -1, 1 }
True: either decrement or increment suceeds
::value != 0
True: either decrement or increment suceeds
::inc_flag one of { 0, 1 }
True: either decrement or increment suceeds
::dec_flag one of { 0, 1 }
::value <= ::inc_flag
::value != orig(::value)
::value <= orig(u)
::inc_flag >= orig(::value)
::inc_flag <= orig(u)
::dec_flag >= orig(::value)
::dec_flag <= orig(u)
===========================================================================
* ==== Thread 2 Invariants ====
===========================================================================
..__VERIFIER_atomic_CAS():::ENTER
True: dec flag is always zero when cas() is called
::dec_flag == e
True: when dec() calls cas(), it is possible for inc() to sneak in and increment the
value 
::value one of { 0, 1 }
True: inc could have already succeeded at the start of this function
::inc_flag one of { 0, 1 }
True: dec flag is always false else dec() would not call cas()
::dec_flag == 0
v has only one value
v != null
u == -1
r != null
flag has only one value
flag != null
::value <= ::inc_flag
::value >= ::dec_flag
::value > u
::inc_flag >= ::dec_flag
::inc_flag > u
===========================================================================
..__VERIFIER_atomic_CAS():::EXIT
True: either dec() or inc() succeeds
::value one of { -1, 1 }
True: either dec() or inc() succeeds
::value != 0
True: either dec() or inc() succeeds
::inc_flag one of { 0, 1 }
True: either dec() or inc() succeeds
::dec_flag one of { 0, 1 }
::value <= ::inc_flag
::value != orig(::dec_flag)
::value >= orig(u)
::inc_flag >= orig(::value)
::inc_flag >= orig(::inc_flag)
::inc_flag >= orig(::dec_flag)
::inc_flag > orig(u)
::dec_flag >= orig(::dec_flag)
::dec_flag > orig(u)
*/
void __VERIFIER_atomic_CAS(
  volatile unsigned *v,
  unsigned e,
  unsigned u,
  unsigned *r,
  volatile unsigned *flag)
{
        // compare the current value of the global with the expected value For
        // both threads, they check to see if the value has changed since they
        // read it and since they performed the CAS (i.e., if their RMW was
        // interrupted)
        //
        // If `v` is what is expected (v == e) then update `v` with the new
        // value (`u`) and set the passed flag to true.
	if(*v == e)
	{
		*flag = 1, *v = u, *r = 1;
	}
        // if `v` is not what is expected, return 0
	else
	{
		*r = 0;
	}
}


/*
===========================================================================
..inc():::ENTER
True: everything is intialized to zero when inc() start
::value == ::inc_flag
::value == ::dec_flag
::value == 0
True const
arg == null
===========================================================================
..inc():::EXIT
return == orig(arg)
True: either inc or dec suceeds upon exit
::value one of { -1, 1 }

True: either inc or dec suceeds upon exit
::value != 0
True: either inc or dec suceeds upon exit
::inc_flag one of { 0, 1 }
True: either inc or dec suceeds upon exit
::dec_flag one of { 0, 1 }
True: const
return == null
::value <= ::inc_flag
::value != orig(::value)
::inc_flag >= orig(::value)
::dec_flag >= orig(::value)
*/
void* inc(void *arg) {
	unsigned inc__v, inc__vn, inc__casret;
	int loopCounter = LOOP_COUNT;

	do {
		inc__v = value;

                // since value is initially zero, this is the case where the
                // decrement thread got there first. We break out in that case
		if(inc__v == 0u-1) {
			return 0; /*increment failed, return min*/
		}

		inc__vn = inc__v + 1;

		__VERIFIER_atomic_CAS(&value, inc__v, inc__vn, &inc__casret, &inc_flag);
		loopCounter--;
		if(loopCounter <= 0) {
			return 0;
		}
	}
	while (inc__casret==0);

}


/*
===========================================================================
..dec():::ENTER
True: inc(() could have already succeeded at the start of dec()
::value one of { 0, 1 }
True: inc(() could have already succeeded at the start of dec()
::inc_flag one of { 0, 1 }
True: dec cannot succeed before it finishes
::dec_flag == 0
arg == null
::value <= ::inc_flag
::value >= ::dec_flag
::inc_flag >= ::dec_flag
===========================================================================
..dec():::EXIT
const
return == orig(arg)
True see above
::value one of { -1, 1 }
::value != 0
True see above
::inc_flag one of { 0, 1 }
True see above
::dec_flag one of { 0, 1 }
return == null
::value <= ::inc_flag
::value != orig(::dec_flag)
::inc_flag >= orig(::value)
::inc_flag >= orig(::inc_flag)
::inc_flag >= orig(::dec_flag)
::dec_flag >= orig(::dec_flag)
*/
void* dec(void *arg) {
	unsigned dec__v, dec__vn, dec__casret;
	int loopCounter = LOOP_COUNT;
	
	do {
		dec__v = value;

                // Originally (i.e.., from SVComp) this condition was 
		// if(dec__v == 0)
                // This doesn't make much sense to me. Value is intially zero
                // so this simply means that the dec thread reached this point
                // before the increment thread. I've changed it to parallel (at
                // least in my head) the behavior of the inc() thread. That is,
                // the dec() thread breaks out if the inc thread goes first.
		if(dec__v == 0u+1) {
			return NULL; /*decrement failed, return max*/
		}

		dec__vn = dec__v - 1;

		__VERIFIER_atomic_CAS(&value, dec__v, dec__vn, &dec__casret, &dec_flag);

		loopCounter--;
		if(loopCounter <= 0) {
			return 0;
		}
	}
	while (dec__casret==0);

	return 0;
}

/*
===========================================================================
..main():::ENTER
True const
::value == ::inc_flag
True const
::value == ::dec_flag
True const
::value == 0
===========================================================================
..main():::EXIT
True const
return == orig(::value)
True const
return == orig(::inc_flag)
True const
return == orig(::dec_flag)
True either the dec() or inc() thread succeeds
::value one of { -1, 1 }
True either the dec() or inc() thread succeeds
::value != 0
True either the dec() or inc() thread succeeds
::inc_flag one of { 0, 1 }
True either the dec() or inc() thread succeeds
::dec_flag one of { 0, 1 }
True const
return == 0
::value <= ::inc_flag
::value != return
::inc_flag >= return
::dec_flag >= return
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
 * Daikon output
 *
 * Number of Invariants: 53
 * Number False: 36
 * Number True: 12
..__VERIFIER_atomic_CAS():::ENTER
False: value can be equal to 0 or 1
::value == ::inc_flag
False: value can be equal to 0 or 1
::value == ::dec_flag
False: value can either be equal to or not equal to e
::value == e
False: value can be equal to 0 or 1
::value == 0
False: value can be equal to 0 or 1
v has only one value
False: u can be either 1 or -1
u == 1
False: this function can fail
r has only one value
False: flag can have multiple values depending on which thread calls the function
flag has only one value
===========================================================================
..__VERIFIER_atomic_CAS():::EXIT
False: value can be -1
::value == ::inc_flag
False: value can be not equal to u in this function if the other thread
succeeds
::value == orig(u)
False: dec_flag can either be 0 or 1
::dec_flag == orig(::value)
False: dec_flag can either be 0 or 1
::dec_flag == orig(::inc_flag)
False: dec_flag can either be 0 or 1
::dec_flag == orig(::dec_flag)
False: dec_flag can either be 0 or 1
::dec_flag == orig(e)
False: value can be -1 or 1
::value == 1
False: dec_flag can either be 0 or 1
::dec_flag == 0
===========================================================================
..dec():::ENTER
False: value can be 0 or 1
::value == ::inc_flag
False: value can be 0 or 1
::value == 1
True: 
::dec_flag == 0
True: const
arg == null
===========================================================================
..dec():::EXIT
False: value can be 0 or 1
::value == ::inc_flag
False: value can be 0 or 1
::value == orig(::value)
False: value can be 0 or 1
::value == orig(::inc_flag)
False: dec_flag can be 0 or 1
::dec_flag == orig(::dec_flag)
True: const
return == orig(arg)
False: value can be 0 or 1
::value == 1
False: dec_flag can be 0 or 1
::dec_flag == 0
True: 
return == null
===========================================================================
..inc():::ENTER
True: all are zero on initialization
::value == ::inc_flag
True: all are zero on initialization
::value == ::dec_flag
True: all are zero on initialization
::value == 0
True: 
arg == null
===========================================================================
..inc():::EXIT
False: value can be 0 or 1
::value == ::inc_flag
False: dec_flag can be 0 or 1
::dec_flag == orig(::value)
False: dec_flag can be 0 or 1
::dec_flag == orig(::inc_flag)
False: dec_flag can be 0 or 1
::dec_flag == orig(::dec_flag)
False: value can be 0 or 1
::value == 1
False: dec_flag can be 0 or 1
::dec_flag == 0
return has only one value
===========================================================================
..main():::ENTER
True: initialized
::value == ::inc_flag
True: initialized
::value == ::dec_flag
True: initialized
::value == 0
===========================================================================
..main():::EXIT
False: could be 0 or 1
::value == ::inc_flag
False: could be 0 or 1
::dec_flag == orig(::value)
False: could be 0 or 1
::dec_flag == orig(::inc_flag)
False: could be 0 or 1
::dec_flag == orig(::dec_flag)
False: could be -1 or 1
::value == 1
False: could be 0 or 1
::dec_flag == 0
True: const
return == 0
*/
