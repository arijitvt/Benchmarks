# Thread 0

Eleven

    ..main():::ENTER
    ::flag1 == ::flag2
    ::flag1 == ::turn
    ::flag1 == ::x
    ::flag1 == 0
    ===========================================================================
    ..main():::EXIT
    ::flag2 == orig(::flag1)
    ::flag2 == orig(::flag2)
    ::flag2 == orig(::turn)
    ::flag2 == orig(::x)
    ::flag1 one of { 0, 1 }
    ::turn one of { 0, 1 }
    ::x one of { 0, 1 }

# Thread 1

Six

    ..thr1():::ENTER
    ::flag1 == ::flag2
    ::flag1 == ::turn
    ::flag1 == ::x
    ::flag1 == 0
    ===========================================================================
    ..thr1():::EXIT
    ::flag1 one of { 0, 1 }
    ::flag2 one of { 0, 1 }
    ::turn one of { 0, 1 }
    ::x one of { 0, 1 }
    ::flag1 >= orig(::flag1)
    ::turn >= orig(::flag1)

# Thread 2

Five

    ..thr2():::ENTER
    ::flag2 == ::x
    ::flag2 == 0
    ::flag1 one of { 0, 1 }
    ::turn one of { 0, 1 }
    ::flag1 >= ::flag2
    ::flag2 <= ::turn
    ===========================================================================
    ..thr2():::EXIT
    ::flag2 == orig(::flag2)
    ::turn == ::x
    ::flag1 one of { 0, 1 }
    ::turn one of { 0, 1 }
    ::flag2 <= orig(::flag1)

Total: 11 + 6 + 5 = 22
