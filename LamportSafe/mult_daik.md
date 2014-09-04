## Daikon\* Results

    ..main():::ENTER
    ::x == ::y
    ::x == ::b1
    ::x == ::b2
    ::x == ::X
    ::x == 0
    ===========================================================================
    ..main():::EXIT
    False
    ::y == ::b1
    False
    ::y == ::b2
    False
    ::y == return
    False
    ::y == orig(::x)
    False
    ::y == orig(::y)
    False
    ::y == orig(::b1)
    False
    ::y == orig(::b2)
    False
    ::y == orig(::X)
    ::x one of { 1, 2 }
    False
    ::y == 0
    ::X one of { 0, 1 }
    False
    ::x > ::y
    False (>=)
    ::x > ::X
    False
    ::y <= ::X
    ===========================================================================
    ..thr1():::ENTER
    ::y == ::b1
    ::y == ::b2
    False: should be zero
    ::x one of { 0, 2 }
    ::y == 0
    False: should be zero
    ::X one of { 0, 1 }
    False
    ::x >= ::y
    False
    ::x >= ::X
    False
    ::y <= ::X
    ===========================================================================
    ..thr1():::EXIT
    False
    ::y == ::b1
    False
    ::y == ::b2
    False
    ::y == ::X
    False
    ::y == orig(::y)
    False
    ::y == orig(::b1)
    False
    ::y == orig(::b2)
    False
    ::x == 1
    False
    ::y == 0
    return == null
    ::x != orig(::x)
    False
    ::x >= orig(::X)
    False
    ::y <= orig(::x)
    False
    ::y <= orig(::X)
    ===========================================================================
    ..thr2():::ENTER
    False
    ::y == ::b1
    False
    ::y == ::b2
    False
    ::y == ::X
    ::x one of { 0, 1 }
    False
    ::y == 0
    ::x >= ::y
    ===========================================================================
    ..thr2():::EXIT
    False
    ::y == ::b1
    False
    ::y == ::b2
    False
    ::y == orig(::y)
    False
    ::y == orig(::b1)
    False
    ::y == orig(::b2)
    False
    ::y == orig(::X)
    False
    ::x == 2
    False
    ::y == 0
    False
    ::X == 1
    return == null
    False (>=)
    ::x > orig(::x)
    False
    ::y <= orig(::x)
    False
    ::X >= orig(::x)

44 false
