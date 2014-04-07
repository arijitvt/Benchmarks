#include <stdio.h>
#include <assert.h>
#include <pthread.h>

int m  = 0 ; 
int IT = 2 ;


void* inc(void *none) {
	int i  = 0;
	int temp = -1;
	while(i < IT) {
		if( m < 1000) {
			temp = m;
			m = temp +1;
			m = IT;
		}
		++i;
	}

}

void* dec(void *none) {
	int i  =0 ;
	int temp = -1;
	while(i < IT) {
		if(m > 0) {
			temp  = m;
			m = temp -1;		
		}
		++i;
	}
}


int main() {
	pthread_t incr,decr;

	pthread_create(&incr,NULL,inc,NULL);
	pthread_create(&decr,NULL,dec,NULL);

	pthread_join(incr,NULL);
        pthread_join(decr,NULL);

	return 0;
}
