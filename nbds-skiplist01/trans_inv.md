## Thread 0

15

    ..fifo_alloc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    scale == 20
    ===========================================================================
    ..fifo_alloc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

15

    ..lwt_thread_init():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::num_keys_ == thread_id
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::lwt_buf_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..lwt_thread_init():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::flags_ == orig(::flags_)
    ::lwt_buf_ != null
    ===========================================================================

16

    ..main():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::num_threads_ == argc
    ::num_keys_ == 0
    ::sl_ == null
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    argv != null
    ===========================================================================
    ..main():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == return
    ::num_keys_ == orig(::num_keys_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::sl_)
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

16

    ..mem_init():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::lwt_buf_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..mem_init():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::lwt_buf_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 0
    ===========================================================================

16

    ..nbd_free():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    x != null
    ===========================================================================
    ..nbd_free():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::num_keys_ == orig(::tid_)
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

16

    ..nbd_init():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::lwt_buf_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..nbd_init():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ===========================================================================

16

    ..nbd_malloc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::num_threads_ one of { 0, 1 }
    ::flags_ has only one value
    ::flags_ != null
    ::num_keys_ <= ::num_threads_
    ::num_keys_ < n
    ::num_threads_ < n
    ===========================================================================
    ..nbd_malloc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::sl_ == orig(::rcu_)
    ::sl_ == orig(::rcu_last_posted_)
    ::sl_ == orig(::flag_state_)
    ::flags_ == orig(::flags_)
    ::num_threads_ one of { 0, 1 }
    ===========================================================================

16

    ..node_alloc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == key
    ::num_keys_ == val
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    num_levels == 24
    ===========================================================================
    ..node_alloc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

16

    ..rcu_thread_init():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::halt_
    ::num_keys_ == id
    ::sl_ == ::pending_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..rcu_thread_init():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ===========================================================================

    ..rdtsc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ == null
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..rdtsc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::lwt_buf_ != null
    ===========================================================================

15

    ..run_test():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..run_test():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

15

    ..sl_alloc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == key_type
    ::num_keys_ == 0
    ::sl_ == null
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..sl_alloc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == ::rcu_
    ::sl_ == ::rcu_last_posted_
    ::sl_ == ::flag_state_
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

15

    ..sl_free():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == sl
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..sl_free():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)

## Thread 1

16

    ..find_preds():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == unlink
    ::sl_ == sl
    ::num_threads_ == n
    ::num_threads_ == key
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::rx_ == 12345
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    preds != null
    succs != null
    ===========================================================================
    ..find_preds():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::sl_ == orig(sl)
    ::rx_ == orig(::rx_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

16

    ..nbd_malloc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::rx_ == 12345
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    n == 32
    ===========================================================================
    ..nbd_malloc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::rx_ == orig(::rx_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 0
    ===========================================================================

16

    ..nbd_rand():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..nbd_rand():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::rcu_ == orig(::rcu_last_posted_)
    ::rcu_ == orig(::flag_state_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

15

    ..node_alloc():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_threads_ == num_levels
    ::num_threads_ == key
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::rx_ == 12345
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    val == 100
    ===========================================================================
    ..node_alloc():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::rx_ == orig(::rx_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

15

    ..random_levels():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == sl
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..random_levels():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::sl_ == orig(sl)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..sl_cas():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::sl_ == sl
    ::num_threads_ == key
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    expectation == -2
    new_val == 100
    ===========================================================================
    ..sl_cas():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..thread_1():::ENTER
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == unused
    ::num_keys_ == 0
    ::sl_ != null
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..thread_1():::EXIT
    ::num_keys_ == ::tid_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::sl_ == orig(::sl_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)

## Thread 2

Thread 2 is the same as 1 except for returns

Thread 2 total: 106

Total: 431
