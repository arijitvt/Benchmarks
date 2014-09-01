
#include <pthread.h>

#define THREAD_COUNT 2
#define LOOP_COUNTER  5

volatile unsigned value = 0;

/*
===========================================================================
 * ==== Thread 1 Invariants
..atomicCAS():::ENTER
True: thread 1 always succeeds at the increment (since we are restricting the
number of spins; our scheduler favors threads with a lower TID).
::value == e
True: either incrementing second or first
::value one of { 0, 1 }
True: see above
v has only one value
v != null
True: either incrementing second or first
u one of { 1, 2 }
True: const
r != null
True: we are incrementing
::value < u
===========================================================================
..atomicCAS():::EXIT
True: always succeeds
::value == orig(u)
True: incremented
::value one of { 1, 2 }
True: incremented
::value > orig(::value)
* ==== End thread 1 invariants ==== 
*
* ==== Thread 2 invariants ==== 
===========================================================================
..atomicCAS():::ENTER
True: thread 2 can go first or second
::value one of { 0, 1 }
True: Thread 2, when it fails, will read a stale value of v and then use up the spins
v has only one value
v != null
True: expected value is sometimes wrong
e one of { 0, 1 }
True: somtimes first and sometimes second
u one of { 1, 2 }
True: const
r != null
::value >= e
::value <= u
e < u
===========================================================================
..atomicCAS():::EXIT
True: an increment either ocurs or fails
::value one of { 1, 2 }
True: an increment either ocurs or fails
::value >= orig(::value)
True: an increment either ocurs or fails
::value > orig(e)
True: an increment either ocurs or fails
::value >= orig(u)
===========================================================================
* ==== End thread 2 invariants ==== 
*/
void  atomicCAS(
  volatile unsigned *v,
  unsigned e,
  unsigned u,
  unsigned *r)
{
	if(*v == e)
	{
		*v = u, *r = 1;
	}
	else
	{
		*r = 0;
	}
}


/*
 * ==== Thread 1 invarients ====
===========================================================================
..thr1():::ENTER
True: init (thread 1 starts first)
::value == 0
True: const
arg == null
===========================================================================
..thr1():::EXIT
True: const
return == orig(arg)
True: one or two threads succeed
::value one of { 1, 2 }
True: const
return == null
True: we are incrementing!
::value > orig(::value)
* ==== End of Thread 1 Invariants ====
*
* ==== Thread 2 Invariants ====
===========================================================================
..thr1():::ENTER
True: thread 2 starts second so thread 1 could have already completed
::value one of { 0, 1 }
True: const
arg == null
===========================================================================
..thr1():::EXIT
True: const
return == orig(arg)
True: either one increment or two
::value one of { 1, 2 }
True: const
return == null
True: incrementing!
::value > orig(::value)
*/
void* thr1(void* arg) {
	unsigned v,vn,casret;
	int counter = LOOP_COUNTER ;

	do {
		v = value;

		if(v == 0u-1) {
			return 0;
		}
                // assertion: v != 0u-1
                // increment value
		vn = v + 1;

		 atomicCAS(&value,v,vn,&casret);
                 // break out of spin so we dont get stuck in an infinite loop
		--counter;
		if(counter <= 0) {
			return 0;
		}
	}
	while (casret==0);
	return 0;
}

/*
===========================================================================
..main():::ENTER
True: init
::value == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::value)
True: either one thread or two threads will suceed in the cas (one has to fail!)
::value one of { 1, 2 }
True: const
return == 0
::value > return
*/
int main(){
	pthread_t t[THREAD_COUNT];
	int i;
	for(i = 0 ; i < THREAD_COUNT; ++i) {
		pthread_create(&t[i],0,thr1,0);
	}

	for(i = 0 ; i < THREAD_COUNT; ++i) {
		pthread_join(t[i],0);
	}
        return 0;
}

/*
 * Daikon output
 * Number of Invariants: 14
 * Number of False Invariants: 3
 * Number of True Invariants: 11
 *
..atomicCAS():::ENTER
False: somtimes it is not what is expected
::value == e
True: either one increment or two
::value one of { 0, 1 }
True: it is a pointer to value
v has only one value
True: either incrmeneintg one or two times
u one of { 1, 2 }
===========================================================================
..atomicCAS():::EXIT
False: sometimes the CAS fails
::value == orig(u)
True: either one inc or two
::value one of { 1, 2 }
===========================================================================
..main():::ENTER
True: init
::value == 0
===========================================================================
..main():::EXIT
False: sometimes there is one inc
::value == 2
True: const
return == 0
===========================================================================
..thr1():::ENTER
True: 
::value one of { 0, 1 }
True: Const
arg == null
===========================================================================
..thr1():::EXIT
True: const
return == orig(arg)
True: either one increment or two
::value one of { 1, 2 }
True: const
return == null
*/
