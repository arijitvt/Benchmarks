## Multi-run Daikon Results

    ..main():::ENTER
    ::flag1 == ::flag2
    ::flag1 == ::turn
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
    ::flag1 == orig(::turn)
    False
    ::flag1 == orig(::x)
    False
    ::flag1 == 0
    False
    ::turn == 1
    ::x one of { 0, 1 }
    False
    ::flag1 <= ::x
    False
    ::turn >= ::x
    ===========================================================================
    ..thr1():::ENTER
    ::flag1 == ::flag2
    ::turn == ::x
    ::flag1 == 0
    False: should be zero
    ::turn one of { 0, 1 }
    False
    ::flag1 <= ::turn
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
    False
    ::turn == 1
    return == null
    False
    ::flag1 <= orig(::turn)
    False
    ::turn >= orig(::turn)
    ===========================================================================
    ..thr2():::ENTER
    False
    ::flag1 == ::flag2
    False
    ::flag1 == ::x
    False
    ::flag1 == 0
    ::turn one of { 0, 1 }
    False
    ::flag1 <= ::turn
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
    ::turn == ::x
    False
    ::flag1 == 0
    False
    ::turn == 1
    return == null
    False
    ::flag1 <= orig(::turn)
    False
    ::turn >= orig(::turn)

Total: 24
