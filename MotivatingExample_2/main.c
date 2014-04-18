#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
int balance = 0 ;

void setLock() {
	pthread_mutex_lock(&lock);
}

void setUnLock() {
	pthread_mutex_unlock(&lock);
}

int getBalance() {
	int bal;
	setLock();
	bal = balance;
	setUnLock();
	return bal;
}

void setBalance(int bal) {
	setLock();
	balance = bal;
	setUnLock();
}

void*  deposit(void *arg) {
	int bal = getBalance();
	bal = bal + 100;
	setBalance(bal);
}

void* withdraw(void *arg) {
	int bal = getBalance();
	bal = bal -100;
	setBalance(bal);
}


int main() {
	pthread_t w,d;
	pthread_create(&d,0,deposit,0);
	pthread_create(&w,0,withdraw,0);

	pthread_join(d,0);
	pthread_join(w,0);

	return 0;

}

