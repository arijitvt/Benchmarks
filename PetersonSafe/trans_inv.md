### Thread 0

Four

    ..main():::ENTER
    ::flag1 == ::flag2
    ::flag1 == ::turn
    ::flag1 == ::x
    ::flag1 == 0
    ===========================================================================
    ..main():::EXIT
    ::flag1 one of { 0, 1 }
    ::flag2 one of { 0, 1 }
    ::turn one of { 0, 1 }
    ::x one of { 0, 1 }

### Thread 1

Four

    ..thr1():::ENTER
    ::flag1 == ::flag2
    ::flag1 == ::turn
    ::flag1 == ::x
    ::flag1 == 0
    ===========================================================================
    ..thr1():::EXIT
    ::x == orig(::x)
    ::flag1 one of { 0, 1 }
    ::flag2 one of { 0, 1 }
    ::turn one of { 0, 1 }

### Thread 2

Five

    ..thr2():::ENTER
    ::flag2 == ::x
    ::flag1 one of { 0, 1 }
    ::flag2 == 0
    ::turn one of { 0, 1 }
    ::flag1 >= ::flag2
    ::flag2 <= ::turn
    ===========================================================================
    ..thr2():::EXIT
    ::flag1 one of { 0, 1 }
    ::flag2 one of { 0, 1 }
    ::turn one of { 0, 1 }
    ::x one of { 0, 1 }
    ::flag2 >= orig(::flag2)

Total: 13
