/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader

   This file is adapted from the Promela code introduced in the paper:
   Using Promela and Spin to verify parallel algorithms
   by Paul McKenney
*/

#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


int idx=0; // boolean to control which of the two elements will be used by readers
  // (idx <= 0) then ctr1 is used
  // (idx >= 1) then ctr2 is used
int ctr1=1, ctr2=0; 
int readerprogress1=0, readerprogress2=0; // the progress is indicated by an integer:
  // 0: reader not yet started
  // 1: reader withing QRCU read-side critical section
  // 2: reader finished with QRCU read-side critical section
pthread_mutex_t mutex; // used to serialize updaters' slowpaths

#define __VERIFIER_nondet_int() \
	 7

#define BIG 5


/* sums the pair of counters forcing weak memory ordering */
#define sum_unordered \
  if (__VERIFIER_nondet_int()) {		\
    sum = ctr1;					\
    sum = sum + ctr2;				\
  } else {					\
    sum = ctr2;					\
    sum = sum + ctr1;				\
  }


#define  __VERIFIER_atomic_use1( myidx) \
	int temp  =ctr1; \
	temp = temp+1; \
	ctr1 = temp; \



//ctr1++;



#define __VERIFIER_atomic_use2(myidx) \
	int temp  =ctr2; \
	temp = temp+1; \
	ctr2 = temp; \

//  ctr2++; 

#define  __VERIFIER_atomic_use_done( myidx)  \
	int temp ;  \
	if (myidx <= 0) {  temp = ctr1; temp = temp -1; ctr1 = temp; }else{temp = ctr2; temp = temp -1; ctr2 = temp;  }    \



void *qrcu_reader1() {
  int myidx;
  /* rcu_read_lock */
  int readCounter = BIG;
  while (1) {
    myidx = idx;
    if (__VERIFIER_nondet_int()) {
      __VERIFIER_atomic_use1(myidx);
      break;
    } else {
      if (__VERIFIER_nondet_int()) {
	__VERIFIER_atomic_use2(myidx);
	break;
      } else {}
    }
    readCounter--;
    if(readCounter<= 0) {
    	return 0;
    }
  }
  readerprogress1 = 1;
  readerprogress1 = 2;
  /* rcu_read_unlock */
  __VERIFIER_atomic_use_done(myidx);
  return 0;
}

void *qrcu_reader2() {
  int myidx;
  int readCounter = BIG;
  /* rcu_read_lock */
  while (1) {
    myidx = idx;
    if (__VERIFIER_nondet_int()) {
      __VERIFIER_atomic_use1(myidx);
      break;
    } else {
      if (__VERIFIER_nondet_int()) {
	__VERIFIER_atomic_use2(myidx);
	break;
      } else {}
    }

    readCounter--;
    if(readCounter<= 0) {
    	return 0;
    }
  }
  readerprogress2 = 1;
  readerprogress2 = 2;
  /* rcu_read_unlock */
  __VERIFIER_atomic_use_done(myidx);
  return 0;
}

void* qrcu_updater() {
  int i;
  int readerstart1, readerstart2;
  int sum;
  sum_unordered;
  if (sum <= 1) { 
	  sum_unordered; 
  }else {
  }

  int updateCounter1 = BIG;
  int updateCounter2 = BIG;
  if (sum > 1) {
    pthread_mutex_lock(&mutex);
    if (idx <= 0) { ctr2++; idx = 1; ctr1--; }
    else { ctr1++; idx = 0; ctr2--; }
    if (idx <= 0) { 
	    while (ctr1 > 0) {
		    if(updateCounter1 <= 0) {
			    pthread_mutex_unlock(&mutex);
			    return 0;
		    }
		    --updateCounter1;
	    }
    }
    else { 
	    while (ctr2 > 0) {
		    if(updateCounter2 <= 0) {
			    pthread_mutex_unlock(&mutex);
			    return 0;
		    }
		    --updateCounter2;
	    }
    }
    pthread_mutex_unlock(&mutex);
  } else {
  
  }
  return 0;
}

int main() {
	srand(time(0));
	pthread_t t1, t2, t3;
	pthread_mutex_init(&mutex, 0);
	pthread_create(&t1, 0, qrcu_reader1, 0);
	pthread_create(&t2, 0, qrcu_reader2, 0);
	pthread_create(&t3, 0, qrcu_updater, 0);
	pthread_join(t1, 0);
	pthread_join(t2, 0);
	pthread_join(t3, 0);
	pthread_mutex_destroy(&mutex);
	return 0;
}
