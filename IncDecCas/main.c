#include <pthread.h>

#define LOOP_COUNT 5
#define THREAD_COUNT 2 

volatile unsigned value = 0;

/*helpers for the property*/
volatile unsigned inc_flag = 0;
volatile unsigned dec_flag = 0;



void __VERIFIER_atomic_CAS(
  volatile unsigned *v,
  unsigned e,
  unsigned u,
  unsigned *r,
  volatile unsigned *flag)
{
	if(*v == e)
	{
		*flag = 1, *v = u, *r = 1;
	}
	else
	{
		*r = 0;
	}
}



void* inc(void *arg) {
	unsigned inc__v, inc__vn, inc__casret;
	int loopCounter = LOOP_COUNT;

	do {
		inc__v = value;

		if(inc__v == 0u-1) {
			return 0; /*increment failed, return min*/
		}

		inc__vn = inc__v + 1;

		__VERIFIER_atomic_CAS(&value,inc__v,inc__vn,&inc__casret,&inc_flag);
		loopCounter--;
		if(loopCounter <= 0) {
			return 0;
		}
	}
	while (inc__casret==0);

}


void* dec(void *arg) {
	unsigned dec__v, dec__vn, dec__casret;
	int loopCounter = LOOP_COUNT;
	
	do {
		dec__v = value;

		if(dec__v == 0) {
			return NULL; /*decrement failed, return max*/
		}

		dec__vn = dec__v - 1;

		__VERIFIER_atomic_CAS(&value,dec__v,dec__vn,&dec__casret,&dec_flag);

		loopCounter--;
		if(loopCounter <= 0) {
			return 0;
		}
	}
	while (dec__casret==0);

	return 0;
}

int main(){
	pthread_t inc_thr,dec_thr;
	pthread_create(&inc_thr,0,inc,0);
	pthread_create(&dec_thr,0,dec,0);
	pthread_join(inc_thr,0);
	pthread_join(dec_thr,0);
	return 0;
}

