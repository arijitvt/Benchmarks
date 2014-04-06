## README
Author: Markus Kusano

`pthread-atomic/peterson_safe.c` from SVComp'13.

## Modifications
1. Added regular C assertions

## Notes
Appears to timeout (more than 10 minutes)

//Arijit
The break statements seems to be placed wrongly because the section where the thread is iterating unless the lock is acquired there it should stay if it is not able to grab the lock.
If it is not able to grab the lock after certain a= # of iteration then it should not jump into critical section. So I removed the break statements with return NULL.

