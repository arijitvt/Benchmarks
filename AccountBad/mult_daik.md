
    ..check_result():::ENTER
    ::x == 1
    ::y == 2
    ::z == 4
    False: should only be one
    ::balance one of { 1, 3 }
    False: could be 0 or 1
    ::withdraw_done == false
    arg == null
    ::x <= ::balance
    ::y != ::balance
    ::z > ::balance
    ===========================================================================
    ..check_result():::EXIT
    ::x == orig(::x)
    ::y == orig(::y)
    ::z == orig(::z)
    ::balance == orig(::balance)
    False: could be 0 or 1
    ::deposit_done == orig(::deposit_done)
    False: could be 0 or 1
    ::withdraw_done == orig(::withdraw_done)
    return == orig(arg)
    ::x == 1
    ::y == 2
    ::z == 4
    ::balance one of { 1, 3 }
    False: could be 0 or 1
    ::withdraw_done == false
    return == null
    False: no relationship
    ::x <= ::balance
    ::y != ::balance
    ::z > ::balance
    ===========================================================================
    ..deposit():::ENTER
    ::x == ::balance
    ::deposit_done == ::withdraw_done
    ::x == 1
    ::y == 2
    ::z == 4
    ::deposit_done == false
    arg == null
    ===========================================================================
    ..deposit():::EXIT
    ::x == orig(::x)
    ::x == orig(::balance)
    ::y == orig(::y)
    ::z == orig(::z)
    False: could be 0 or 1
    ::withdraw_done == orig(::deposit_done)
    False: could be modified
    ::withdraw_done == orig(::withdraw_done)
    return == orig(arg)
    ::x == 1
    ::y == 2
    ::z == 4
    False: could be -1 or 3
    ::balance == 3
    ::deposit_done == true
    ::withdraw_done == false
    return == null
    ===========================================================================
    ..main():::ENTER
    ::x == ::y
    ::x == ::z
    ::x == ::balance
    ::deposit_done == ::withdraw_done
    ::x == 0
    ::deposit_done == false
    ===========================================================================
    ..main():::EXIT
    ::deposit_done == ::withdraw_done
    ::x == 1
    ::y == 2
    ::z == 4
    ::balance == -1
    ::deposit_done == true
    return == 99
    ===========================================================================
    ..withdraw():::ENTER
    ::x == 1
    ::y == 2
    ::z == 4
    ::balance == 3
    False: could be zero or 1
    ::deposit_done == true
    False: could be zero or 1
    ::withdraw_done == false
    arg == null
    ===========================================================================
    ..withdraw():::EXIT
    ::x == orig(::x)
    ::y == orig(::y)
    ::z == orig(::z)
    False: could be zero or 1
    ::deposit_done == ::withdraw_done
    False: could be zero or 1
    ::deposit_done == orig(::deposit_done)
    return == orig(arg)
    ::x == 1
    ::y == 2
    ::z == 4
    False: could be -3 or -1
    ::balance == -1
    False: could be zero or 1
    ::deposit_done == true
    return == null

Total: 
