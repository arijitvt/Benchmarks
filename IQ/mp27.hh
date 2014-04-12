// Author: Chao Wang <chaowang@vt.edu>
// Date: 12/27/2012
//
// Example for Exercise 27 in the "Multiprocessor Programming" book.
//
// The implementation is NOT linearizable
//

#include "../AtomicInteger/AtomicInteger.hh"

#include <pthread.h>
#include <assert.h>
#include <iostream>

#define MAX_NUM_ITEMS  16

using namespace std;

class EmptyException
{
public:
  const char *ShowReason() const { return "EmptyException."; }
};


 class IQueue {
  AtomicInteger head;
  AtomicInteger tail;
  int items[MAX_NUM_ITEMS];

public:
  IQueue() {
    head.set(0);
    tail.set(0);
    for(int i=0; i<MAX_NUM_ITEMS; i++) {
      items[i] = NULL;
    }
  }
  
  void enq(int x) {
    int slot;
    do {
      slot = tail.get();
    } while (! tail.compareAndSet(slot, slot+1));
    items[slot] = x;
  }

  int deq() {
    int value=0;
    int slot;
    do {
      slot = head.get();
      value = items[slot];
      if (value == NULL)
        return 0; //assert(0);
//        throw EmptyException();
    } while (! head.compareAndSet(slot, slot+1));
    return value;
  }




//template <class T> class IQueue {
//  AtomicInteger head;
//  AtomicInteger tail;
//  T* items[MAX_NUM_ITEMS];
//
//public:
//  IQueue() {
//    head.set(0);
//    tail.set(0);
//    for(int i=0; i<MAX_NUM_ITEMS; i++) {
//      items[i] = NULL;
//    }
//  }
//
//  void enq(T* x) {
//    int slot;
//    do {
//      slot = tail.get();
//    } while (! tail.compareAndSet(slot, slot+1));
//    items[slot] = x;
//  }
//
//  T* deq() {
//    T* value;
//    int slot;
//    do {
//      slot = head.get();
//      value = items[slot];
//      if (value == NULL)
//        throw EmptyException();
//    } while (! head.compareAndSet(slot, slot+1));
//    return value;
//  }
};

