// Author: Chao Wang <chaowang@vt.edu>
// Date: 12/27/2012
//
// Example for Exercise 32 in the "Multiprocessor Programming" book.
//
// It's called the Herlihy/Wing queue.
//
// The implementation is linearizable, but "enq()" does not have a 
// linearization point.

#include "../AtomicInteger/AtomicInteger.hh"
#include "../AtomicReference/AtomicReference.hh"
#include <pthread.h>
#include <assert.h>
#include <iostream>

#define CAPACITY  16
using namespace std;

template <class T> class HWQueue {
  AtomicReference<T> items[CAPACITY];
  AtomicInteger tail;

public:

  HWQueue() {
    for(int i=0; i<CAPACITY; i++) {
      items[i].set(NULL);
    }
    tail.set(0);
  }
  
  void enq(T* x) {
    int i = tail.getAndIncrement();
    //cout<<"i= "<<i<<endl;
    items[i].set(x);
  }

  int deq() {
    while(true) {
      int range = tail.get();
      for (int i=0; i<range; i++) {
        T* value = items[i].getAndSet(NULL);
        if (value != NULL) {
          return value->get();
        }
      }
    }
  }

};

