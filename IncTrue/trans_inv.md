### Thread 0

2

    ..main():::ENTER
    ::value == ::m
    ::value == 0
    ===========================================================================
    ..main():::EXIT
    ::m == orig(::m)
    ::value one of { 1, 2 }

### Thread 1

2

    ..thr1():::ENTER
    ::value == ::m
    ::value == 0
    ===========================================================================
    ..thr1():::EXIT
    ::m == orig(::m)
    ::value one of { 1, 2 }

### Thread 2

4

    ..thr1():::ENTER
    ::value one of { 0, 1 }
    ::m one of { 0, 1 }
    ===========================================================================
    ..thr1():::EXIT
    ::value one of { 1, 2 }
    ::m == 0
    ::value > orig(::value)
    ::m <= orig(::m)

Total: 8
