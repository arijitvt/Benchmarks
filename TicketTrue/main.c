#include <pthread.h>

#define FAILED 3 //this is already and the limit of what we can handle

#define NEXT(e) ((e + 1) % FAILED)

#define LOOP_COUNT 5
#define THREAD_COUNT 2


volatile unsigned next_ticket = 0;
volatile unsigned now_serving = 0;

int c = 0;

unsigned __VERIFIER_atomic_fetch_and_increment__next_ticket(){
	unsigned value;

		if(NEXT(next_ticket) == now_serving){ 
			value = FAILED;
		}
		else
		{
			value = next_ticket;
			next_ticket = NEXT(next_ticket);
		}

	return value;
}

int acquire_lock(){
	unsigned my_ticket; 
	int loopCounter  = LOOP_COUNT;

	my_ticket = __VERIFIER_atomic_fetch_and_increment__next_ticket(); //returns old value; arithmetic overflow is harmless (Alex: it is not if we have 2^64 threads)

	if(my_ticket == FAILED){
		return -1;
	}else{
		while(1){
			//pause(my_ticket - now_serving);
			// consume this many units of time
			// on most machines, subtraction works correctly despite overflow
			if(now_serving == my_ticket){
				break;
			}
			--loopCounter;
			if(loopCounter<=0) {
				return -1;
			}
		}
	}

	return 0;
}

void release_lock(){
	now_serving++;
}

void* thr1(void* arg){
	int temp;
	if( -1 == acquire_lock()) {
		return 0;
	}
	//	c = c+1;
	temp = c;
	temp = temp +1;
	c = temp;

	//	c = c -1;
	temp  = c;
	temp = temp -1;
	c = temp;

	release_lock();

	return 0;
}

int main(){
  pthread_t t[THREAD_COUNT];
  int i;
  for (i = 0 ; i < THREAD_COUNT; ++i) {
	  pthread_create(&t[i],0,thr1,0);
  }

  for (i = 0 ; i < THREAD_COUNT; ++i) {
	  pthread_join(t[i],0);
  }
  return 0;
}

