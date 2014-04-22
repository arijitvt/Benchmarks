#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>


#include <time.h>


const int SIGMA = 2;

int *array;
int array_index = -1;


void *thread(void * arg)
{
	int temp = array_index;
	temp = temp+1;
	array_index = temp;
	printf("Array Index is %d\n",array_index);
	array[array_index] = 1;
	return 0;
}


int main()
{
	int tid, sum;
	pthread_t *t;

	t = (pthread_t *)malloc(sizeof(pthread_t) * SIGMA);
	//array = (int *)malloc(sizeof(int) * SIGMA);
	array = (int *)calloc(SIGMA,sizeof(int));


	for (tid=0; tid<SIGMA; tid++) {
		pthread_create(&t[tid], 0, thread, 0);
	}

	for (tid=0; tid<SIGMA; tid++) {
		pthread_join(t[tid], 0);
	}

	for (tid=sum=0; tid<SIGMA; tid++) {
		sum += array[tid];
	}

	printf("The sum is %d\n",sum);

	return 0;
}

