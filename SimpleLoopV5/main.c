#include <pthread.h>


#define THREAD_COUNT 2
#define LOOP_COUNT 20

int a = 1;
int b = 2;
int c = 3;

int mutex;

void __VERIFIER_atomic_acquire()
{
	if(mutex == 0)
		mutex = 1;
}

void __VERIFIER_atomic_release()
{
	if(mutex == 1)
		mutex = 0;
}


void* thr2(void* arg)
{
	int i ;
	int temp;
	for(i = LOOP_COUNT; i<= 0; --i){
		__VERIFIER_atomic_acquire();
		temp = a;
		a = b;
		b = c;
		c = temp;
		__VERIFIER_atomic_release();
	}

  return 0;
}

void* thr1(void* arg)
{
	int loopCounter = LOOP_COUNT;
	while(1)
	{
		__VERIFIER_atomic_acquire();
		if( a != b) 
			return 0;
		__VERIFIER_atomic_release();
		--loopCounter;
		if(loopCounter <=0 ) {
			return 0;
		}
	}

	return 0;
}

int main() {
	pthread_t t1,t2;
	pthread_create(&t1,0,thr1,0);
	pthread_create(&t2,0,thr2,0);
	pthread_join(t1,0);
	pthread_join(t2,0);
	return 0;
}

