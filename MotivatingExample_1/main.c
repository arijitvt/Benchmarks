#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "hook.h"

struct Example{
	int a;
	int b;
	int c;
};

typedef struct Example Example;

Example *ex;

void* thr1(void *arg) {
	int result = 0 ;
	if(ex != NULL) {
		ex->a = 100;
		result = hook_assert(ex->a == 100);
		if(result == -1) {
			return 0;
		}
		ex->b = 200;
		result = hook_assert(ex->a == 100 && ex->b == 200);
		if(result == -1) {
			return 0;
		}
		ex->c= 300;
		result = hook_assert(ex->a == 100 && ex->b== 200 && ex->c == 300);
		if(result == -1) {
			return 0;
		}
	}
}

void* thr2(void *arg) {
	ex = (Example*)malloc(sizeof(Example));
}

int main() {
	pthread_t t1,t2;

	pthread_create(&t1,0,thr1,0);
	pthread_create(&t2,0,thr2,0);

	pthread_join(t1,0);
	pthread_join(t2,0);

	return 0;
}
