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
	if(ex != NULL) {
		ex->a = 100;
		hook_assert(ex->a == 100);
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
