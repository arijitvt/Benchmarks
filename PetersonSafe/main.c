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


void *thr1() {
	int count=0;
	flag1 = 1;
	turn = 1;

	int temp;

	while (flag2==1 && turn==1) {
		if (count++ > IT) return NULL;
	}

	// begin: critical section
	temp = x;
	temp = temp+1;
	x = temp;
	hook_assert(x == temp+1);
	//assert(x<=0);
	// end: critical section
	flag1 = 0;
	return NULL;
}

void *thr2() {
	int count=0;
	flag2 = 1;
	turn = 0;
	int temp;
	while (flag1==1 && turn==0) { 
		if(count++ >IT) return NULL;
	}
	// begin: critical section
	temp =x;
	temp = temp-1;
	x = temp;
	hook_assert(x == temp -1);
	//assert(x>=1);
	// end: critical section
	flag2 = 0;
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
