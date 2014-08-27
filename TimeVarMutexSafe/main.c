/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader

   This file is adapted from the example introduced in the paper:
   Thread-Modular Verification for Shared-Memory Programs 
   by Cormac Flanagan, Stephen Freund, Shaz Qadeer.
*/

#include <pthread.h>
#include <assert.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;

int block;
int busy; // boolean flag indicating whether the block has been allocated to an inode
int inode;
pthread_mutex_t m_inode; // protects the inode
pthread_mutex_t m_busy; // protects the busy flag

/*
 *
===========================================================================
..allocator():::ENTER
True: allocator starts first and sees main()'s init
::inode == ::busy
True: allocator starts first and sees main()'s init
::inode == ::block
True: allocator starts first and sees main()'s init
::inode == 0
===========================================================================
..allocator():::EXIT
True: inode is always zero and busy and inode are always set
::inode == ::busy
::inode == ::block
::inode == 1
return == null
*/
void *allocator(){
  pthread_mutex_lock(&m_inode);
  if(inode == 0){
    pthread_mutex_lock(&m_busy);
    busy = 1;
    pthread_mutex_unlock(&m_busy);
    inode = 1;
  }
  block = 1;
 // assert(block == 1);
  pthread_mutex_unlock(&m_inode);
  return NULL;
}

/*
 *
===========================================================================
..de_allocator():::ENTER
True: busy mirrors inode in allocaotr()
::inode == ::busy
True: busy mirrors inode in allocaotr()
::inode == ::block
True: busy mirrors inode in allocaotr()
::inode one of { 0, 1 }
===========================================================================
..de_allocator():::EXIT
True: busy mirrors inode in allocaotr()
::inode == ::busy
True: inode is always set (at some point) and block is always set (in the same critical section)
::inode == ::block
True: inode is either set or not set depending on the race of allocator() and deallocator()
::inode one of { 0, 1 }
return == null
*/
void *de_allocator(){
  pthread_mutex_lock(&m_busy);
  if(busy == 0){
    block = 0;
   // assert(block == 0);
  }
  pthread_mutex_unlock(&m_busy);
  return ((void *)0);
}
 
/*
 *
===========================================================================
..main():::ENTER
True: init;
::inode == ::busy
True: init;
::inode == ::block
True: init;
::inode == 0
===========================================================================
..main():::EXIT
True: if inode is set busy is always set
::inode == ::busy
True: inode is always set and block is always set
::inode == ::block
True: const
return == orig(::inode)
True: const
return == orig(::busy)
True: const
return == orig(::block)
True: inode is always set
::inode == 1
True: const
return == 0
*/
int main() {
  pthread_t t1, t2;
  //__VERIFIER_assume(inode == busy);
  pthread_mutex_init(&m_inode, 0);
  pthread_mutex_init(&m_busy, 0);
  pthread_create(&t1, 0, allocator, 0);
  pthread_create(&t2, 0, de_allocator, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  pthread_mutex_destroy(&m_inode);
  pthread_mutex_destroy(&m_busy);
  return 0;
}

/*
 * Daikon Output
 * Num Inv: 27
 * Num true: 18
 * Num False: 9
 *
===========================================================================
..allocator():::ENTER
True:
::block == ::busy
True:
::block == ::inode
True:
::block == 0
===========================================================================
..allocator():::EXIT
True:
::block == ::busy
True:
::block == ::inode
True:
::block == 1
True:
return == null
===========================================================================
..de_allocator():::ENTER
False: inode/block/busy can be either 0 or 1
::block == ::busy
False: inode/block/busy can be either 0 or 1
::block == ::inode
False: inode/block/busy can be either 0 or 1
::block == 1
===========================================================================
..de_allocator():::EXIT
False: inode/busy/block can be either 0 or 1
::block == ::busy
False: inode/busy/block can be either 0 or 1
::block == ::inode
False: inode/busy/block can be either 0 or 1
::block == orig(::block)
False: inode/busy/block can be either 0 or 1
::block == orig(::busy)
False: inode/busy/block can be either 0 or 1
::block == orig(::inode)
False: inode/busy/block can be either 0 or 1
::block == 1
True: const
return == null
===========================================================================
..main():::ENTER
True: init
::block == ::busy
True: init
::block == ::inode
True: init
::block == 0
===========================================================================
..main():::EXIT
True:
::block == ::busy
True:
::block == ::inode
True: const
return == orig(::block)
True: const
return == orig(::busy)
True: const
return == orig(::inode)
True:
::block == 1
True: const
return == 0
*/
