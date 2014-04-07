#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#include "hook.h"

int m  = 0 ; 
int IT = 2 ;

pthread_mutex_t lock;

void* inc(void *none) {
	int i  = 0;
	int temp = -1;
	while(i < IT) {
		pthread_mutex_lock(&lock);
		if( m < 1000) {
			temp = m;
			m = temp +1;
			m = IT;
		}
		++i;
	        pthread_mutex_unlock(&lock);
	}

}

void* dec(void *none) {
	int i  =0 ;
	int temp = -1;
	while(i < IT) {
	        pthread_mutex_lock(&lock);
		if(m > 0) {
			temp  = m;
			m = temp -1;		
		}
		++i;
		pthread_mutex_unlock(&lock);
	}
}


int main() {
	pthread_t incr,decr;
	pthread_mutex_init(&lock,0);	

	pthread_create(&incr,NULL,inc,NULL);
	pthread_create(&decr,NULL,dec,NULL);

	pthread_join(incr,NULL);
        pthread_join(decr,NULL);

	pthread_mutex_destroy(&lock);
	return 0;
}
