## Thread 0

6

    ..main():::ENTER
    ::deposit_done == ::withdraw_done
    ::deposit_done == ::balance
    ::deposit_done == ::y
    ::deposit_done == ::z
    ::deposit_done == ::x
    ::deposit_done == 0
    ===========================================================================
    ..main():::EXIT
    ::deposit_done == ::withdraw_done
    ::deposit_done == ::x
    ::deposit_done == 1
    ::balance == -1
    ::y == 2
    ::z == 4

## Thread 1

6

    ..check_result():::ENTER
    ::deposit_done == ::withdraw_done
    ::balance == ::x
    ::deposit_done == 0
    ::balance == 1
    ::y == 2
    ::z == 4
    arg == null
    ===========================================================================
    ..check_result():::EXIT
    ::y == orig(::y)
    ::z == orig(::z)
    ::x == orig(::x)
    ::deposit_done one of { 0, 1 }
    ::withdraw_done one of { 0, 1 }
    ::balance one of { -1, 1, 3 }

## Thread 2

6

    ..deposit():::ENTER
    ::deposit_done == ::withdraw_done
    ::balance == ::x
    ::deposit_done == 0
    ::balance == 1
    ::y == 2
    ::z == 4
    arg == null
    ===========================================================================
    ..deposit():::EXIT
    ::deposit_done == 1
    ::deposit_done == ::x
    ::withdraw_done one of { 0, 1 }
    ::balance one of { -1, 3 }
    ::y == 2
    ::z == 4

## Thread 3

6

    ..withdraw():::ENTER
    ::deposit_done one of { 0, 1 }
    ::withdraw_done == 0
    ::balance one of { 1, 3 }
    ::y == 2
    ::z == 4
    ::x == 1
    ===========================================================================
    ..withdraw():::EXIT
    ::deposit_done one of { 0, 1 }
    ::withdraw_done == 1
    ::balance one of { -3, -1 }
    ::y == 2
    ::z == 4
    ::withdraw_done == ::x

Total: 24
