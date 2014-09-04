## Transition Invariants

## Thread 0

One transition invariant:

    ..main():::ENTER
    ::num == 0
    ===========================================================================
    ..main():::EXIT
    return == orig(::num)

## Thread 1

One transition invariant:


    ..thread1():::ENTER
    ::num == 1
    ===========================================================================
    ..thread1():::EXIT
    ::num == orig(::num)

## Thread 2

One transition invariant:

    ::num == 1
    ===========================================================================
    ..thread2():::EXIT
    ::num one of { 0, 1 }

Total of 3
