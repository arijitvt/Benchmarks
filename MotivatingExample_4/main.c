#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>

#include "hook.h"


#include <time.h>


const int SIGMA = 2;
int sum = 2;

int array_index = 2;


void *thread(void * arg)
{
	int temp = array_index;
	int o = temp;
	temp = temp+1;
	array_index = temp;

	hook_assert( array_index == o+1);
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

