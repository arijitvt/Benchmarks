## README
From SVComp'13 (`pthread_atomic/lamport_safe.c`)

## Modifcations
1. Add normal C assertions

## Notes
Timesout on PSet

//Arijit Chattopadhyay
Compared with the SVCOM 14

Removed the break statement with return. One break has to be there otherwise the threads can not enter into the critical section.
