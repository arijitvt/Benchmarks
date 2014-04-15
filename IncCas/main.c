
#include <pthread.h>
#include "hook.h"


#define THREAD_COUNT 2
#define LOOP_COUNTER  5


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

volatile unsigned value = 0;

void* thr1(void* arg) {
	unsigned v,vn,casret;
	int counter = LOOP_COUNTER ;
	int orig;
	orig = value;

	do {
		v = value;

		if(v == 0u-1) {
			return 0;
		}

		vn = v + 1;

		 atomicCAS(&value,v,vn,&casret);
		--counter;
		if(counter <= 0) {
			return 0;
		}
	}
	while (casret==0);

	hook_assert(value == orig+1);	
	return 0;
}

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

