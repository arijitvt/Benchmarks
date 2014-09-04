
    ..main():::ENTER
    ::value == ::m
    ::value == 0
    ===========================================================================
    ..main():::EXIT
    ::m == orig(::value)
    ::m == orig(::m)
    False
    ::value == 2
    ::m == 0
    return == 0
    ===========================================================================
    ..thr1():::ENTER
    ::value one of { 0, 1 }
    False: could be zero or 1
    ::m == 0
    arg == null
    False: val could be 0 and m could be 1
    ::value >= ::m
    ===========================================================================
    ..thr1():::EXIT
    ::m == orig(::m)
    return == orig(arg)
    ::value one of { 1, 2 }
    ::m == 0
    return == null
    ::value > ::m
    ::value > orig(::value)
    ::m <= orig(::value)

Total: 3
