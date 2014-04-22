#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "hook.h"

struct Example { int a, b, c};
typedef struct Example Example;

Example A[128] ;
Example *p = NULL;


void* thr1 (void *) {
  tmp = p;
  if (tmp != NULL) {
    p->a = 100;
    p->b = 200;
    p->c = 300;
    
    hook_assert( tmp->a == 100 && tmp->b == 200 && tmp->c == 300 );
  }
  return 0;
}


void * thr2(void *) {
  i = rand() % 127+1;
  p = & A[i];
  return 0;
}


int main() {
	int i;
	for(i = 0 ; i < 128;++i) {
		A[i] = (Example *) malloc(sizeof(Example));
	}
	p = A[0];
	pthread_t t1,t2;
	pthread_create(&t1,0,thr1,0);
	pthread_create(&t2,0,thr2,0);
	pthread_join(t1,0);
	pthread_join(t2,0);
	return 0;
}
