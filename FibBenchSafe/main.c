#include <pthread.h>
#include <assert.h>

#include "hook.h"

int i=1, j=1;

#define NUM 5

void *t1(void* arg)
{
	int k = 0;
	int temp;
	int orig;

	for (k = 0; k < NUM; k++) {
	      //  i+=j;
	      //  The below code is converted to do the CS
		orig = i;
		temp = i;
		temp = temp+j;
		i = temp;
		int result;
		result = hook_assert( i == orig+j);
		if( result == -1) {
			return 0;
		}
	}
	return NULL;
}

void* t2(void* arg)
{
	int k = 0;
	int temp;
	int orig;

	for (k = 0; k < NUM; k++) {
		// j+=i;
		// Equivalent code is below
		orig = j;
		temp = j;
		temp = temp + i;
		j = temp;
		int result;
		result = hook_assert( j == orig+i);
		if(result == -1) {
			return 0;
		}

	}
	return NULL;
}

int
main(int argc, char **argv)
{
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  return 0;
}
