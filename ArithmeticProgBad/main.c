#include <pthread.h>
#include <assert.h>
#include <stdio.h>

#define N 3

int num = 0 ;
unsigned long total = 0;
int flag;

pthread_mutex_t m;
pthread_cond_t empty, full;

void *thread1(void *arg)
{
	int i;

	i = 0;
	int temp;
		while (i < N){
			pthread_mutex_lock(&m);
			while (num > 0) 
				pthread_cond_wait(&empty, &m);

			//    num++;
			//    Eq is below
			temp = num;
			temp = temp +1;
			num = temp;

			printf ("produce ....%d\n", i);
			pthread_mutex_unlock(&m);

			pthread_cond_signal(&full);

			i++;
		}

	return NULL;
}

void *thread2(void *arg)
{
  int j;

  j = 0;
  int temp;
  unsigned long temp_total;
  while (j < N){
    pthread_mutex_lock(&m);
    while (num == 0) 
      pthread_cond_wait(&full, &m);

//    total=total+j;
//    eq is below
    temp_total = total ;
    temp_total = temp_total +j;
    total = temp_total;

    printf("total ....%ld\n",total);    
//    num--;
//    eq is below
    temp = num;
    temp = temp -1;
    num = temp;
    printf("consume ....%d\n",j);
    pthread_mutex_unlock(&m);
    
    pthread_cond_signal(&empty);
    j++;    
  }
 // total=total+j;
 // eq is below
  temp_total = total ;
  temp_total = temp_total +j;
  total = temp_total;
  printf("total ....%ld\n",total);
  flag=1;

  return NULL;
}


int main(void)
{
  pthread_t  t1, t2;

  num = 0;
  total = 0;

  pthread_mutex_init(&m, 0);
  pthread_cond_init(&empty, 0);
  pthread_cond_init(&full, 0);
  
  pthread_create(&t1, 0, thread1, 0);
  pthread_create(&t2, 0, thread2, 0);

  pthread_join(t1, 0);
  pthread_join(t2, 0);

  return 0;
}

