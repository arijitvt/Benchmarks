## Notes

Similar to the other nbds examples, there is an error in the invariants
calculated by Daikon in the `ll_cas()` function. Daikon misses a run where
thread 2 runs before thread 1 causing the return value to not contain `1`. PCB,
HaPSet and DPOR find the invariant correctly.
