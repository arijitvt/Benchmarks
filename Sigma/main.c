#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>


#include <time.h>


const int SIGMA = 2;

int *array;
int array_index;


void *thread(void * arg)
{
	int temp = array_index;
	sleep(rand()%2+1);
	array[temp] = 1;
	return 0;
}


int main()
{
	int tid, sum;
	pthread_t *t;
	srand(time(0));

	t = (pthread_t *)malloc(sizeof(pthread_t) * SIGMA);
	array = (int *)malloc(sizeof(int) * SIGMA);


	for (tid=0; tid<SIGMA; tid++) {
		pthread_create(&t[tid], 0, thread, 0);
		array_index++;
	}

	for (tid=0; tid<SIGMA; tid++) {
		pthread_join(t[tid], 0);
	}

	for (tid=sum=0; tid<SIGMA; tid++) {
		sum += array[tid];
	}

        //assert(sum == SIGMA);

	return 0;
}

