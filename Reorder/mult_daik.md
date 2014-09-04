
    ..checkThread():::ENTER
    ::iSet == ::iCheck
    ::iSet == 2
    False: 0 or 1
    ::a == 1
    False -1 or 0
    ::b == -1
    param == null
    ===========================================================================
    ..checkThread():::EXIT
    ::iSet == ::iCheck
    ::iSet == orig(::iSet)
    ::iSet == orig(::iCheck)
    False: could be modified
    ::a == orig(::a)
    False: could be modified
    ::b == orig(::b)
    return == orig(param)
    ::iSet == 2
    False: could be modified
    ::a == 1
    False: could be modified
    ::b == -1
    return == null
    ===========================================================================
    ..main():::ENTER
    ::iSet == ::iCheck
    ::a == ::b
    ::iSet == 2
    ::a == 0
    argc == 1
    argv has only one value
    argv != null
    ===========================================================================
    ..main():::EXIT
    ::iSet == ::iCheck
    ::iSet == orig(::iSet)
    ::iSet == orig(::iCheck)
    ::a == orig(argc)
    return == orig(::a)
    return == orig(::b)
    ::iSet == 2
    ::a == 1
    ::b == -1
    return == 0
    ===========================================================================
    ..setThread():::ENTER
    ::iSet == ::iCheck
    ::iSet == 2
    ::a one of { 0, 1 }
    ::b one of { -1, 0 }
    ::iSet > ::a
    ::iSet > ::b
    ::a >= ::b
    ===========================================================================
    ..setThread():::EXIT
    ::iSet == ::iCheck
    ::iSet == orig(::iSet)
    ::iSet == orig(::iCheck)
    return == orig(param)
    ::iSet == 2
    ::a == 1
    ::b == -1
    return == null
    ::iSet > orig(::a)
    ::iSet > orig(::b)
    ::a >= orig(::a)
    ::a > orig(::b)
    ::b < orig(::a)
    ::b <= orig(::b)

Total: 6
