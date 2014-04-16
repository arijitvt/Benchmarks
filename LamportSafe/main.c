/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;

#include "hook.h"

#define BIG 5

int x, y;
int b1, b2; // boolean flags
int X; // boolean variable to test mutual exclusion

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
	hook_assert(X == 0);
	//assert(X <= 0);
	// end: critical section
	y = 0;
	b1 = 0;
	return NULL;
}

void *thr2() {
	int count1=BIG;
	int count2=BIG;
	int count3=BIG;
	int count4=BIG;
	int temp;
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
	hook_assert(X == 1);
	//assert(X >= 1);
	// end: critical section
	y = 0;
	b2 = 0;
	return NULL;
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
