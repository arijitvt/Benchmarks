/*
 * See the bottom of this file for an example daikon output
 */
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

pthread_mutex_t m;
//int nondet_int();
int x, y, z, balance;
_Bool deposit_done=0, withdraw_done=0;

/* Function entry invariants
 * ===========================================================================    
 * ..deposit():::ENTER
 * The current program model assumes that if a thread is created first then its
 * entrance is also first. Since the deposit thread is created first it "sees"
 * the program as if the withdraw thread has not been executed
 * ::deposit_done == ::withdraw_done
 * ::balance == ::x
 * ::deposit_done == 0
 * ::balance == 1
 * True: Constant
 * ::y == 2
 * ::z == 4
 * arg == null
 * ===========================================================================
 *
 * Function exit invariants
 * ===========================================================================
 * ..deposit():::EXIT
 * True: deposit_done is always one after this function
 * ::deposit_done == ::x
 * ::deposit_done == orig(::balance)
 * ::deposit_done == orig(::x)
 * ::y == orig(::y)
 * ::z == orig(::z)
 * return == orig(arg)
 * ::deposit_done == 1
 * True: the withdraw thread can sometimes execute before the depost thread
 * ::withdraw_done one of { 0, 1 }
 * Balance is three if the deposit thread runs before the withdraw thread (1 +
 * 3). Similarly 3 if withdraw goes first.
 * ::balance one of { -1, 3 }
 * ::balance != 0
 * ::y == 2
 */
void *deposit(void *arg) 
{
  pthread_mutex_lock(&m);
  balance = balance + y;
  deposit_done=1;
  pthread_mutex_unlock(&m);

  return NULL;
}

/* Function entry invariants:
 * 
===========================================================================    
..withdraw():::ENTER
 * This is true: the call to deposit() can interleave either before or after
 * the call to withdraw().
::deposit_done one of { 0, 1 }
 * This is true: there is only one call to withdraw in the program so withdraw
 * done cannot be set to one before this function is called
::withdraw_done == 0
 * This is true: balance is equal to one if deposit has not been called yet
 * (balance is initialized to one). If deposit has already been called then
 * balance will be three (deposit inserts 2, with the balance initally at 1, so
 * the result is three). 
::balance one of { 1, 3 }
 * True: These three values are all constants at the time this function is called
 * (they are initialized by main).
::y == 2
::z == 4
::x == 1
 * True: arg is always null
arg == null
::deposit_done >= ::withdraw_done
::deposit_done < ::balance
::deposit_done < ::y
::deposit_done < ::z
::deposit_done <= ::x
::withdraw_done < ::balance
::balance != ::y
::balance < ::z
::balance >= ::x
===========================================================================

 * Function exit invariants
===========================================================================
..withdraw():::EXIT
 * True: x is one
::withdraw_done == ::x
 * True: x is one and constants
::withdraw_done == orig(::x)
 * True: these are constsnts
::y == orig(::y)
::z == orig(::z)
 * True: arg is unchanged and NULL
return == orig(arg)
 * True: same reasoning as with entry case
::deposit_done one of { 0, 1 }
 * True: the deposit is complete
::withdraw_done == 1
 * True: If withdraw goes first, then balance is -3. If deposit goes first then
 * balance is -1
::balance one of { -3, -1 }
 * True: these are constsnts
::y == 2
::z == 4
 * True: the return value is constant
return == null
::deposit_done <= ::withdraw_done
::deposit_done > ::balance
::deposit_done < ::y
::deposit_done < ::z
::deposit_done >= orig(::deposit_done)
::deposit_done >= orig(::withdraw_done)
::deposit_done <= orig(::balance)
::withdraw_done > ::balance
::withdraw_done >= orig(::deposit_done)
::withdraw_done <= orig(::balance)
::balance < ::y
::balance < ::z
::balance < orig(::deposit_done)
::balance < orig(::withdraw_done)
::balance < orig(::balance)
::y > orig(::deposit_done)
::y != orig(::balance)
::z > orig(::deposit_done)
::z > orig(::balance)
*/
void *withdraw(void *arg) 
{
  pthread_mutex_lock(&m);
  balance = balance - z;
  withdraw_done=1;
  pthread_mutex_unlock(&m);

  return NULL;
}


/*
 * 
..check_result():::ENTER
True: since check result starts first, both are set to 0
::deposit_done == ::withdraw_done
True: balance is initialized by main to x
::balance == ::x
::deposit_done == 0
::balance == 1
constants
::y == 2
::z == 4
const
arg == null
===========================================================================
..check_result():::EXIT
constants
::y == orig(::y)
::z == orig(::z)
::x == orig(::balance)
::x == orig(::x)
return == orig(arg)
true depends on the ordering of the other threads
::deposit_done one of { 0, 1 }
::withdraw_done one of { 0, 1 }
true, never zero
::balance != 0
::y == 2
::z == 4
::x == 1
return == null
::deposit_done != ::balance
::deposit_done < ::y
::deposit_done < ::z
::deposit_done <= ::x
::deposit_done >= orig(::deposit_done)
::withdraw_done != ::balance
::withdraw_done < ::y
::withdraw_done < ::z
::withdraw_done <= ::x
::withdraw_done >= orig(::deposit_done)
::balance != ::y
::balance < ::z
::balance != orig(::deposit_done)
*/
void *check_result(void *arg) 
{
  pthread_mutex_lock(&m);
  if (deposit_done && withdraw_done) {
   // assert(balance == (x - y) - z); /* BAD */
   	assert(1);
  }
  pthread_mutex_unlock(&m);

  return NULL;
}

/*
 *
..main():::ENTER
::deposit_done == ::withdraw_done
::deposit_done == ::balance
::deposit_done == ::y
::deposit_done == ::z
::deposit_done == ::x
::deposit_done == 0
===========================================================================
..main():::EXIT
::deposit_done == ::withdraw_done
::deposit_done == ::x
::deposit_done == 1
::balance == -1
const
::y == 2
::z == 4
return == 99
*/
int main() 
{
  pthread_t t1, t2, t3;

  pthread_mutex_init(&m, 0);

  x = 1;
  y = 2;
  z = 4;
  balance = x;

  pthread_create(&t3, 0, check_result, 0);
  pthread_create(&t1, 0, deposit, 0);
  pthread_create(&t2, 0, withdraw, 0);

  pthread_join(t3, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  assert(balance == -1);

  return 99;
}
/*
 * Daikon output
 * Number of invariants: 78
 * Incorrect invariants: 22
 *
===========================================================================
..check_result():::ENTER
::deposit_done == ::withdraw_done
True: const
::x == 1
True: const
::y == 2
True: const
::z == 4
False: should be 1
::balance == -1
False: could be false
::deposit_done == true
True, const
arg == null
===========================================================================
..check_result():::EXIT
True: const
::x == orig(::x)
True: const
::y == orig(::y)
True: const
::z == orig(::z)
False: could be modified
::balance == orig(::balance)
False
::deposit_done == ::withdraw_done
False
::deposit_done == orig(::deposit_done)
False
::deposit_done == orig(::withdraw_done)
True const
return == orig(arg)
True const
::x == 1
True const
::y == 2
True const
::z == 4
False: depends on interleaving
::balance == -1
False: depends on interleaving
::deposit_done == true
return == null
===========================================================================
..deposit():::ENTER
False: depends on interleaving
::x == ::balance
False: depends on interleaving (withdraw could be 0
::deposit_done == ::withdraw_done
True; const
::x == 1
True; const
::y == 2
True; const
::z == 4
True: set by this func
::deposit_done == false
True: const
arg == null
===========================================================================
..deposit():::EXIT
True: const
::x == orig(::x)
False: depends on interleaving
::x == orig(::balance)
True: const
::y == orig(::y)
True: const
::z == orig(::z)
False: interleaving
::withdraw_done == orig(::deposit_done)
False: interleaving
::withdraw_done == orig(::withdraw_done)
True: const
return == orig(arg)
True: const
::x == 1
True: const
::y == 2
True: const
::z == 4
False: interleaving
::balance == 3
False: interleaving
::deposit_done == true
False: interleaving
::withdraw_done == false
True: const
return == null
===========================================================================
..main():::ENTER
True: const
::x == ::y
True: const
::x == ::z
True: const
::x == ::balance
True: const
::deposit_done == ::withdraw_done
True: const
::x == 0
True: const
::deposit_done == false
===========================================================================
..main():::EXIT
True:
::deposit_done == ::withdraw_done
True:
::x == 1
True:
::y == 2
True:
::z == 4
True:
::balance == -1
True:
::deposit_done == true
True:
return == 99
===========================================================================
..withdraw():::ENTER
True: const
::x == 1
True: const
::y == 2
True: const
::z == 4
False: interleaving
::balance == 3
False: interleaving
::deposit_done == true
True: set by this thread
::withdraw_done == false
True: const
arg == null
===========================================================================
..withdraw():::EXIT
True: const
::x == orig(::x)
True: const
::y == orig(::y)
True: const
::z == orig(::z)
False: interleaving
::deposit_done == ::withdraw_done
False: interleaving
::deposit_done == orig(::deposit_done)
True: const
return == orig(arg)
True: const
::x == 1
True: const
::y == 2
True: const
::z == 4
False: interleaving
::balance == -1
False: interleaving
::deposit_done == true
True: const
return == null
 */
