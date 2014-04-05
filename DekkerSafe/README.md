From SVCOMP'13

Location:

    pthread-atomic/dekker_safe.c

Modifications:

1. Added explicit assertions
1. Removed `__VERIFIER_ASSUME()` call

## Notes
I considered this to timeout on DPOR at 14551 runs (about 2 hours runtime)

//Arijit Chattopadhyay
Compared with the SVCOM 14. This is same.
