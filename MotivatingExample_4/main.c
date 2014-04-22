#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>


#include <time.h>


const int SIGMA = 2;
int sum = 2;

int array_index = 0 ;


void *thread(void * arg)
{
	int temp = array_index;
	temp = temp+1;
	array_index = temp;
	return 0;
}


int main()
{
	int tid;
	pthread_t *t;

	t = (pthread_t *)malloc(sizeof(pthread_t) * SIGMA);


	for (tid=0; tid<SIGMA; tid++) {
		pthread_create(&t[tid], 0, thread, 0);
	}

	for (tid=0; tid<SIGMA; tid++) {
		pthread_join(t[tid], 0);
	}

	return 0;
}

