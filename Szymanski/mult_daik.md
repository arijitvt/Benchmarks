## Daikon\* Results

    ..main():::ENTER
    ::flag1 == ::flag2
    ::flag1 == ::x
    ::flag1 == 0
    ===========================================================================
    ..main():::EXIT
    False
    ::flag1 == ::flag2
    False
    ::flag1 == return
    False
    ::flag1 == orig(::flag1)
    False
    ::flag1 == orig(::flag2)
    False
    ::flag1 == orig(::x)
    False
    ::flag1 == 0
    ::x one of { 0, 1 }
    False
    ::flag1 <= ::x
    ===========================================================================
    ..thr1():::ENTER
    ::flag1 == ::flag2
    ::flag1 == 0
    False, should be 0
    ::x one of { 0, 1 }
    False (==)
    ::flag1 <= ::x
    ===========================================================================
    ..thr1():::EXIT
    False
    ::flag1 == ::flag2
    False
    ::flag1 == ::x
    False
    ::flag1 == orig(::flag1)
    False
    ::flag1 == orig(::flag2)
    False
    ::flag1 == 0
    return == null
    False
    ::flag1 <= orig(::x)
    ===========================================================================
    ..thr2():::ENTER
    False flag2 is zero but the others may or may not be zero
    ::flag1 == ::flag2
    False
    ::flag1 == ::x
    False
    ::flag1 == 0
    ===========================================================================
    ..thr2():::EXIT
    False
    ::flag1 == ::flag2
    False
    ::flag1 == orig(::flag1)
    False
    ::flag1 == orig(::flag2)
    False
    ::flag1 == orig(::x)
    False
    ::flag1 == 0
    False
    ::x == 1
    return == null

Total: 24
