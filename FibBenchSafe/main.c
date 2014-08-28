#include <pthread.h>
#include <assert.h>

int i=1, j=1;

#define NUM 5

/*
===========================================================================
..t1():::ENTER
True: main's init
::i == ::j
True: main's init
::i == 1
const
arg == null
===========================================================================
..t1():::EXIT
return == orig(arg)
return == null
True: incremented always inorder to exit
::i > orig(::i)
True: somtimes incremented to exit
::j >= orig(::i)
*/
void *
t1(void* arg)
{
  int k = 0;

  for (k = 0; k < NUM; k++)
    i+=j;

  return NULL;
//  pthread_exit(NULL);
	
}

/*
===========================================================================
..t2():::ENTER
True: incremented or not incremented by t1
::i >= 1
True: init by main
::j == 1
arg == null
::i >= ::j
===========================================================================
..t2():::EXIT
return == orig(arg)
return == null
True: sometimes incremented
::i >= orig(::i)
::i >= orig(::j)
True: always incremented
::j > orig(::i)
::j > orig(::j)
*/
void *
t2(void* arg)
{
  int k = 0;

  for (k = 0; k < NUM; k++)
    j+=i;

  return NULL;

//  pthread_exit(NULL);
}

/*
===========================================================================
..main():::ENTER
True: init
::i == ::j
::i == argc
::i == 1
argv != null
===========================================================================
..main():::EXIT
return == 0
True: everything is atleast incremented once
::i > return
::i > orig(::i)
::j > return
::j > orig(::i)
 */
int
main(int argc, char **argv)
{
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  if (i > 144 || j > 144) {
#if 0
    goto ERROR;
    ERROR:
      assert(0);
      ;
#endif
  }

  return 0;
}
/*
 * Daikon output
 * Num inv: 24
 * Num True: 14
 * Num False: 10
 * 
===========================================================================
..main():::ENTER
True: init
::i == ::j
True: init
::i == argc
True: init
::i == 1
True
argv has only one value
===========================================================================
..main():::EXIT
False: could not be these values depending on interleaving
::i == 6
False: could not be these values depending on interleaving
::j == 31
True: const
return == 0
===========================================================================
..t1():::ENTER
True: sees main's init
::i == ::j
True: sees main's init
::i == 1
True: const
arg == null
===========================================================================
..t1():::EXIT
False: j could be incremented
::j == orig(::i)
False: j could be incremented
::j == orig(::j)
True: const
return == orig(arg)
False: could change depending on if thread2 is always running concurrently
::i == 6
False: could change depending on if thread2 is always running concurrently
::j == 1
True: const
return == null
===========================================================================
..t2():::ENTER
False: could be 1
::i == 6
True: always 1 
::j == 1
True: const
arg == null
===========================================================================
..t2():::EXIT
False: could be modified
::i == orig(::i)
True: const
return == orig(arg)
False: could be larger
::i == 6
False: could be larger
::j == 31
True: const
return == null
*/
