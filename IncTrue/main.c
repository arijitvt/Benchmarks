
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

