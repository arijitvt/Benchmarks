
/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>

#define LOOP_COUNT 5

int flag1 = 0, flag2 = 0; // integer flags 
int x; // boolean variable to test mutual exclusion

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

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
