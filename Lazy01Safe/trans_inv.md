## Transition Invariants

### Thread 0

One

    ..main():::ENTER
    ::data == 0
    ===========================================================================
    ..main():::EXIT
    ::data == 3

### Thread 1

Two: 

    ..thread1():::ENTER
    ::data == 0
    ===========================================================================
    ..thread1():::EXIT
    ::data one of { 1, 3 }
    ::data > orig(::data)

### Thread 2

Two:


    ..thread2():::ENTER
    ::data one of { 0, 1 }
    ===========================================================================
    ..thread2():::EXIT
    ::data one of { 2, 3 }
    ::data > orig(::data)

Total: 5
