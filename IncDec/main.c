
#include <pthread.h>
#include "hook.h"



volatile unsigned value = 0, m = 0;

void __VERIFIER_atomic_acquire()
{
	if(m == 0 ) {
		m = 1;
	}
}

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

void* inc(void *arg) {


	__VERIFIER_atomic_acquire();
	if(value == 0u-1) {
		__VERIFIER_atomic_release();
	}else{
		inc_v = value;
		inc_flag = 1;
		value = inc_v + 1; /*set flag, then update*/
		hook_assert( value == inc_v+1);
		__VERIFIER_atomic_release();
	}

}

void* dec(void *arg) {
	__VERIFIER_atomic_acquire();
	if(value == 0) {
		__VERIFIER_atomic_release();
	}else{
		dec_v = value;
		dec_flag = 1;
		value = dec_v - 1; /*set flag, then update*/
		hook_assert(value == dec_v-1);
		__VERIFIER_atomic_release();
	}
}


int main(){
	pthread_t inc_thr,dec_thr;
	pthread_create(&inc_thr,0,inc,0);
	pthread_create(&dec_thr,0,dec,0);
	pthread_join(inc_thr,0);
	pthread_join(dec_thr,0);
	return 0;
}

