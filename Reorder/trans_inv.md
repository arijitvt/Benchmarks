### Thread 0

4

    ..main():::ENTER
    ::iSet == ::iCheck
    ::a == ::b
    ::iSet == 2
    ::a == 0
    ===========================================================================
    ..main():::EXIT
    ::iSet == ::iCheck
    ::iSet == 2
    ::a == 1
    ::b == -1

### Thread 1

4

    ..setThread():::ENTER
    ::iSet == ::iCheck
    ::a == ::b
    ::iSet == 2
    ::a == 0
    ===========================================================================
    ..setThread():::EXIT
    ::iSet == ::iCheck
    ::iSet == orig(::iSet)
    ::a == 1
    ::b == -1

### Thread 2

4

    ..setThread():::ENTER
    ::iSet == ::iCheck
    ::iSet == 2
    ::a one of { 0, 1 }
    ::b one of { -1, 0 }
    param == null
    ::iSet > ::a
    ::iSet > ::b
    ::a >= ::b
    ===========================================================================
    ..setThread():::EXIT
    ::iSet == ::iCheck
    ::iSet == 2
    ::a == 1
    ::b == -1

Total: 12
