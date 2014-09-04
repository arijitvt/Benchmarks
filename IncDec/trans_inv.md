### Thread 0

2

    ..main():::ENTER
    ::value == ::m
    ::value == 0
    ===========================================================================
    ..main():::EXIT
    ::m == orig(::m)
    ::value one of { 0, 1 }

### Thread 1

6

    ..__VERIFIER_atomic_acquire():::ENTER
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == ::inc_v
    ::value == ::dec_v
    ::value == 0
    ::m one of { 0, 1 }
    ===========================================================================
    ..__VERIFIER_atomic_acquire():::EXIT
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == ::inc_v
    ::value == ::dec_v
    ::value == 0
    ::m == 1
    ===========================================================================

6

    ..__VERIFIER_atomic_release():::ENTER
    ::m == ::inc_flag
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m == 1
    ::dec_flag one of { 0, 1 }
    ::inc_v == 0
    ::value <= ::m
    ::value != ::dec_flag
    ::value >= ::inc_v
    ::m >= ::dec_flag
    ::dec_flag >= ::inc_v
    ===========================================================================
    ..__VERIFIER_atomic_release():::EXIT
    ::value one of { 0, 1 }
    ::m == 0
    ::m == ::inc_v
    ::inc_flag == 1
    ::dec_flag == ::dec_v
    ::dec_flag one of { 0, 1 }

6

    ===========================================================================
    ..inc():::ENTER
    ::value == ::inc_flag
    ::value == ::dec_flag
    ::value == ::inc_v
    ::value == ::dec_v
    ::value == 0
    ::m one of { 0, 1 }
    arg == null
    ::value <= ::m
    ===========================================================================
    ..inc():::EXIT
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m == 0
    ::inc_flag == 1
    ::dec_flag one of { 0, 1 }
    ::m == ::inc_v

### Thread 2

6

    ..__VERIFIER_atomic_acquire():::ENTER
    ::dec_flag == ::inc_v
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m one of { 0, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag == 0
    ===========================================================================
    ..__VERIFIER_atomic_acquire():::EXIT
    ::dec_flag == ::inc_v
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m == 1
    ::inc_flag one of { 0, 1 }
    ::dec_flag == orig(::dec_flag)
    ===========================================================================

6
    ..__VERIFIER_atomic_release():::ENTER
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m one of { 0, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }
    ::inc_v == 0
    ::value <= ::inc_flag
    ::value >= ::inc_v
    ===========================================================================
    ..__VERIFIER_atomic_release():::EXIT
    ::value one of { 0, 1 }
    ::m == 0
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }
    ::m == ::inc_v
    ::dec_flag == ::dec_v
    ===========================================================================

6

    ..dec():::ENTER
    ::dec_flag == ::inc_v
    ::dec_flag == ::dec_v
    ::value one of { 0, 1 }
    ::m one of { 0, 1 }
    ::inc_flag one of { 0, 1 }
    ::dec_flag == 0
    arg == null
    ::value <= ::inc_flag
    ::value >= ::dec_flag
    ::m <= ::inc_flag
    ::m >= ::dec_flag
    ::inc_flag >= ::dec_flag
    ===========================================================================
    ..dec():::EXIT
    ::inc_flag one of { 0, 1 }
    ::dec_flag one of { 0, 1 }
    ::value one of { 0, 1 }
    ::m == ::inc_v
    ::m == 0
    ::dec_flag == ::dec_v

Total: 38
