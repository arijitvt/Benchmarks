//
// Example for Exercise 32 in the "Multiprocessor Programming" book.
//
// It's called the Herlihy/Wing queue.
//
// The implementation is linearizable.
//
// However, "enq()" does not have a linearization point.
//

#include "mp32.hh"
#include "../Integer/Integer.hh"


using namespace std;

//-----The Queue under test-----
HWQueue<Integer> x;

//-----The Queue items ---------
Integer i1  ( 1);
Integer i10 (10);

void* foo (void*)
{
  x.enq( &i1 );           //ENQ
  cout << "enq: " << 1 << endl;
  return 0;
}

void* bar (void*)
{
  x.enq( &i10 );        //ENQ
  cout << "enq: " << 10 << endl;
  int b = x.deq(); //DEQ
  cout << "deq: "<< b << endl;

  return 0;
}

int main(void)
{
  cout<<"-------"<<endl;

  pthread_t t1, t2;
  pthread_create(&t1, 0, foo, 0);
  pthread_create(&t2, 0, bar, 0);

  pthread_join(t1,0);
  pthread_join(t2,0);

  return 0;
}

 
