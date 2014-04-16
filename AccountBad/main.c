#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#include "hook.h"

pthread_mutex_t m;
//int nondet_int();
//int x, y, z, balance;
int x = 1;
int y = 2;
int z = 4;
int balance;
_Bool deposit_done=0, withdraw_done=0;

void *deposit(void *arg) 
{
	int temp;
	int orig;
	pthread_mutex_lock(&m);  
	//  balance = balance + y;
	//  Eq is below
        orig = balance;
	temp = balance;
	temp = temp +y;
	balance = temp;
	deposit_done=1;
	hook_assert( balance == orig +y);
	pthread_mutex_unlock(&m);

	return NULL;
}

void *withdraw(void *arg) 
{
	int temp;
	int orig;
	pthread_mutex_lock(&m);  
	//balance = balance - z;
	//eq is below
        orig = balance;
	temp = balance;
	temp = temp -z;
	balance = temp;
	withdraw_done=1;
	hook_assert(balance == orig - z);
	pthread_mutex_unlock(&m);

	return NULL;
}

void *check_result(void *arg) 
{
  pthread_mutex_lock(&m);
  if (deposit_done && withdraw_done) {
   	assert(1);
  }
  pthread_mutex_unlock(&m);

  return NULL;
}

int main() 
{
  pthread_t t1, t2, t3;

  pthread_mutex_init(&m, 0);

//  x = 1;
//  y = 2;
//  z = 4;
//  balance = x;

  balance = x;
  pthread_create(&t3, 0, check_result, 0);
  pthread_create(&t1, 0, deposit, 0);
  pthread_create(&t2, 0, withdraw, 0);

  pthread_join(t3, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
