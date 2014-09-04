
    ..atomicCAS():::ENTER
    False: value >= e
    ::value == e
    ::value one of { 0, 1 }
    v has only one value
    v != null
    u one of { 1, 2 }
    r != null
    ::value < u
    ===========================================================================
    ..atomicCAS():::EXIT
    False >=
    ::value == orig(u)
    ::value one of { 1, 2 }
    ::value > orig(::value)
    ===========================================================================
    ..main():::ENTER
    ::value == 0
    ===========================================================================
    ..main():::EXIT
    False
    ::value == 2
    return == 0
    ===========================================================================
    ..thr1():::ENTER
    ::value one of { 0, 1 }
    arg == null
    ===========================================================================
    ..thr1():::EXIT
    return == orig(arg)
    ::value one of { 1, 2 }
    return == null
    ::value > orig(::value)
