### Thread 0
3

    ..main():::ENTER
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == 0
    ===========================================================================
    ..main():::EXIT
    ::value one of { -1, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }

### Thread 1

3

    ..__VERIFIER_atomic_CAS():::ENTER
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == 0
    ===========================================================================
    ..__VERIFIER_atomic_CAS():::EXIT
    ::value one of { -1, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }
    ===========================================================================

3

    ..inc():::ENTER
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == 0
    arg == null
    ===========================================================================
    ..inc():::EXIT
    ::value one of { -1, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }

### Thread 2

3

    ..__VERIFIER_atomic_CAS():::ENTER
    ::value one of { 0, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag == 0
    ===========================================================================
    ..__VERIFIER_atomic_CAS():::EXIT
    ::inc_flag == orig(::inc_flag)
    ::value one of { -1, 1 }
    ::dec_flag one of { 0, 1 }
    ===========================================================================
3

    ..dec():::ENTER
    ::value one of { 0, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag == 0
    ===========================================================================
    ..dec():::EXIT
    ::value one of { -1, 1 }
    ::inc_flag >= orig(::inc_flag)
    ::dec_flag >= orig(::dec_flag)

Total: 15
