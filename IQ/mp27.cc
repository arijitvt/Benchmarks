//
// Example for Exercise 27 in the "Multiprocessor Programming" book.
//
// The implementation is NOT linearizable.
//
// When running it under Inspect, there will be an ASSERT failure in run# 2
//

#include <iostream>
#include "mp27.hh"
#include "../Integer/Integer.hh"

using namespace std;

//-----The Queue under test-----
IQueue *x;

void* foo(void*) {
	x->enq(3);           //ENQ
	cout << "Enq: " << 3 << endl;
        //int a = x->deq();    //DEQ
	//cout << "deq: " << a << endl;
	return 0;
}

void* bar(void*) {
        x->enq(5);           //ENQ
	cout << "Enq: " << 5 << endl;
	int b = x->deq();    //DEQ
        cout << "deq: " << b << endl;
	return 0;
}

int main(void) {
	cout<<"----------"<<endl;
	x = new IQueue();

	pthread_t t1, t2;

        /*
	x->enq(1);           //ENQ
	x->enq(2);
	cout << "deq: " << x->deq() << endl;
	cout << "deq: " << x->deq() << endl;
        */
	pthread_create(&t1, 0, foo, 0);
	pthread_create(&t2, 0, bar, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	return 0;
}

