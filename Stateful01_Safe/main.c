#include <pthread.h> 
#include <assert.h>

#include "hook.h"

pthread_mutex_t  ma, mb;
int data1 = 10;
int data2 = 10;

void * thread1(void * arg)
{
	int temp;
	int orig;
	int result;
	pthread_mutex_lock(&ma);
	//data1++;
	//Eqivalent is below
	orig = data1;
	temp = data1;
	temp = temp+1;
	data1= temp;
	
	result = hook_assert( data1 == orig+1);
	if(result == -1) {
		return 0;
	}
	

	pthread_mutex_unlock(&ma);

	pthread_mutex_lock(&ma);
	//  data2++;
	//  Equivalent is below
	orig = data2;
	temp = data2;
	temp = temp+1;
	data2= temp;
	
	result = hook_assert( data2 == orig+1);
	if(result == -1) {
		return 0;
	}
	
	pthread_mutex_unlock(&ma);
}


void * thread2(void * arg)
{  
	int temp;
	int orig;
	int result;
	pthread_mutex_lock(&ma);
	//  data1+=5;
	//  Equivalent is below
        orig = data1;
	temp = data1;
	temp = temp +5;
	data1 = temp;

	result = hook_assert( data1 == orig+5);
	if(result == -1) {
		return 0;
	}

	pthread_mutex_unlock(&ma);

	pthread_mutex_lock(&ma);
	//  data2-=6;
	//  Equivalent is below
	orig = data2;
	temp = data2;
	temp = temp -6;
	data2 = temp;
	
	result = hook_assert( data2 == orig-6);
	if(result == -1) {
		return 0;
	}
	pthread_mutex_unlock(&ma);
}


int main()
{
  pthread_t  t1, t2;

  pthread_mutex_init(&ma, 0);
  pthread_mutex_init(&mb, 0);

  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);
  
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  return 0;
}

