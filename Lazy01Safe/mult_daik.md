## Results running Daikon Multiple Times

    ..main():::ENTER
    True
    ::data == 0
    ===========================================================================
    ..main():::EXIT
    return == orig(::data)
    True
    ::data == 3
    True
    return == 0
    ===========================================================================
    ..thread1():::ENTER
    False: should be zero
    ::data one of { 0, 2 }
    arg == null
    ===========================================================================
    ..thread1():::EXIT
    return == orig(arg)
    True
    ::data one of { 1, 3 }
    return == null
    ::data > orig(::data)
    ===========================================================================
    ..thread2():::ENTER
    True:
    ::data one of { 0, 1 }
    arg == null
    ===========================================================================
    ..thread2():::EXIT
    return == orig(arg)
    True
    ::data one of { 2, 3 }
    return == null
    ::data > orig(::data)
    ===========================================================================
    ..thread3():::ENTER
    False
    ::data == 3
    arg == null
    ===========================================================================
    ..thread3():::EXIT
    False
    ::data == orig(::data)
    return == orig(arg)
    False
    ::data == 3
    return == null

Total: 4 incorrect
