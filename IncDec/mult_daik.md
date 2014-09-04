    ..__VERIFIER_atomic_acquire():::ENTER
    False value could be zero or one
    ::value == ::inc_flag
    False m could be 1
    ::m == ::dec_flag
    False could be 1
    ::m == ::inc_v
    False could be 1
    ::m == ::dec_v
    ::value one of { 0, 1 }
    False could be 1
    ::m == 0
    False could both be zero
    ::value >= ::m
    ===========================================================================
    ..__VERIFIER_atomic_acquire():::EXIT
    False (<=)
    ::value == ::inc_flag
    False (>=)
    ::value == orig(::value)
    False (<=)
    ::value == orig(::inc_flag)
    ::dec_flag == ::inc_v
    ::dec_flag == ::dec_v
    False: m could be zero or one
    ::dec_flag == orig(::m)
    ::dec_flag == orig(::dec_flag)
    ::dec_flag == orig(::inc_v)
    ::dec_flag == orig(::dec_v)
    ::value one of { 0, 1 }
    ::m == 1
    ::dec_flag == 0
    ::value <= ::m
    ::value >= ::dec_flag
    ===========================================================================
    ..__VERIFIER_atomic_release():::ENTER
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    False: could be zero
    ::m == 1
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }
    ::inc_v == 0
    False, could be >=
    ::value <= ::m
    False
    ::value <= ::inc_flag
    False
    ::value >= ::inc_v
    False: 0 or 1 for both
    ::m >= ::inc_flag
    False: 0 or 1 for both
    False: 0 or 1 for both
    ::m >= ::dec_flag
    ::inc_flag >= ::dec_flag
    False: 0 or 1 for both
    ::inc_flag >= ::inc_v
    False: 0 or 1 for both
    ::dec_flag >= ::inc_v
    ===========================================================================
    ..__VERIFIER_atomic_release():::EXIT
    False culd be modified
    ::value == orig(::value)
    ::m == ::inc_v
    ::m == orig(::inc_v)
    False: could be modified
    ::inc_flag == orig(::inc_flag)
    False could be modified
    ::dec_flag == ::dec_v
    False could be modified
    ::dec_flag == orig(::dec_flag)
    False could be modified
    ::dec_flag == orig(::dec_v)
    False could be modified
    ::value one of { 0, 1 }
    ::m == 0
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }
    ::value >= ::m
    ::value <= ::inc_flag
    False
    ::value <= orig(::m)
    ::m <= ::inc_flag
    ::m <= ::dec_flag
    ::inc_flag >= ::dec_flag
    False: could be set to 1
    ::inc_flag <= orig(::m)
    False: could be set to 1
    ::dec_flag <= orig(::m)
    ===========================================================================
    ..dec():::ENTER
    False: <=
    ::value == ::inc_flag
    False: could be 1
    ::m == ::dec_flag
    False: could be 1
    ::m == ::inc_v
    False: could be 1
    ::m == ::dec_v
    ::value one of { 0, 1 }
    False: could be 1
    ::m == 0
    arg == null
    False: either could be zero or one
    ::value >= ::m
    ===========================================================================
    ..dec():::EXIT
    False could be zero or one
    ::value == ::m
    False could be zero or one
    ::value == ::inc_v
    False could be zero or one
    ::value == orig(::m)
    False could be zero or one
    ::value == orig(::dec_flag)
    False could be zero or one
    ::value == orig(::inc_v)
    False could be zero or one
    ::value == orig(::dec_v)
    False could be zero or one
    ::inc_flag == ::dec_flag
    False could be zero or one
    ::inc_flag == ::dec_v
    False could be zero or one
    ::inc_flag == orig(::value)
    False could be zero or one
    ::inc_flag == orig(::inc_flag)
    False could be zero or one
    ::value == 0
    ::inc_flag one of { 0, 1 }
    return has only one value
    return != null
    False
    ::value <= ::inc_flag
    ===========================================================================
    ..inc():::ENTER
    False: m could be zero or one
    ::value == ::m
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == ::inc_v
    ::value == ::dec_v
    ::value == 0
    arg == null
    ===========================================================================
    ..inc():::EXIT
    False could be deced
    ::value == ::inc_flag
    False: could be zero or one
    ::m == ::dec_flag
    False: could be zero or one
    ::m == ::inc_v
    False: could be zero or one
    ::m == ::dec_v
    ::m == orig(::value)
    False: could be zero or one on entry
    ::m == orig(::m)
    ::m == orig(::inc_flag)
    ::m == orig(::dec_flag)
    ::m == orig(::inc_v)
    ::m == orig(::dec_v)
    False: zero or one
    ::value == 1
    ::m == 0
    return has only one value
    return != null
    ===========================================================================
    ..main():::ENTER
    ::value == ::m
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == ::inc_v
    ::value == ::dec_v
    ::value == 0
    ===========================================================================
    ..main():::EXIT
    ::m == ::inc_v
    ::m == orig(::value)
    ::m == orig(::m)
    ::m == orig(::inc_flag)
    ::m == orig(::dec_flag)
    ::m == orig(::inc_v)
    ::m == orig(::dec_v)
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m == 0
    ::inc_flag == 1
    ::dec_flag one of { 0, 1 }
    return == 0
    ::value >= ::m
    ::value <= ::inc_flag
    ::value != ::dec_flag
    ::m <= ::dec_flag
    ::inc_flag >= ::dec_flag

Total:
