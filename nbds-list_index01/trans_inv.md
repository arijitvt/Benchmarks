## Thread 0

14

    ..fifo_alloc():::ENTER
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::ll_ == null
    ::tid_ == 0
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    scale == 20
    ===========================================================================
    ..fifo_alloc():::EXIT
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..ll_alloc():::ENTER
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == key_type
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::ll_ == null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..ll_alloc():::EXIT
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

13

    ..ll_free():::ENTER
    ::ll_ == ll
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..ll_free():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

13

    ..lwt_thread_init():::ENTER
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::lwt_buf_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::tid_ == thread_id
    ::ll_ == null
    ::tid_ == 0
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..lwt_thread_init():::EXIT
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::flags_ == orig(::flags_)
    ===========================================================================

13

    ..main():::ENTER
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::num_threads_ == argc
    ::ll_ == null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    argv != null
    ===========================================================================
    ..main():::EXIT
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..mem_init():::ENTER
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::lwt_buf_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::ll_ == null
    ::tid_ == 0
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..mem_init():::EXIT
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::lwt_buf_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..nbd_free():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    x != null
    ===========================================================================
    ..nbd_free():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..nbd_init():::ENTER
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::lwt_buf_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::ll_ == null
    ::tid_ == 0
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..nbd_init():::EXIT
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::flags_ == orig(::flags_)
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ===========================================================================

12

    ..nbd_malloc():::ENTER
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::ll_ == null
    ::tid_ == 0
    ::num_threads_ one of { 0, 1 }
    ::flags_ has only one value
    ::flags_ != null
    ::tid_ <= ::num_threads_
    ::tid_ < n
    ::num_threads_ < n
    ===========================================================================
    ..nbd_malloc():::EXIT
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::flags_ == orig(::flags_)
    ::num_threads_ one of { 0, 1 }
    ===========================================================================

14

    ..node_alloc():::ENTER
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == key
    ::tid_ == val
    ::ll_ == null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..node_alloc():::EXIT
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..rcu_thread_init():::ENTER
    ::ll_ == ::pending_
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::num_threads_
    ::tid_ == ::halt_
    ::tid_ == id
    ::ll_ == null
    ::tid_ == 0
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..rcu_thread_init():::EXIT
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::pending_ != null
    ::num_threads_ == 1
    ===========================================================================

14

    ..rdtsc():::ENTER
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::ll_ == null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..rdtsc():::EXIT
    ::ll_ == ::rcu_
    ::ll_ == ::rcu_last_posted_
    ::ll_ == ::flag_state_
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)

## Thread 1

14

    ..find_pred():::ENTER
    ::ll_ == ll
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::num_threads_ == key
    ::num_threads_ == help_remove
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    pred_ptr != null
    item_ptr != null
    ===========================================================================
    ..find_pred():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..ll_cas():::ENTER
    ::ll_ == ll
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::num_threads_ == key
    ::num_threads_ == new_val
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    expectation == -2
    ===========================================================================
    ..ll_cas():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..nbd_free():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ has only one value
    ::tid_ == 0
    ::pending_ has only one value
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ has only one value
    ::flags_ has only one value
    x has only one value
    ===========================================================================
    ..nbd_free():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..nbd_malloc():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    n == 24
    ===========================================================================
    ..nbd_malloc():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..node_alloc():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::num_threads_ == key
    ::num_threads_ == val
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..node_alloc():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

14

    ..t1_main():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == tid
    ::ll_ != null
    ::tid_ == 0
    ::pending_ != null
    ::num_threads_ == 1
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..t1_main():::EXIT
    ::ll_ == orig(::ll_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::num_threads_ == orig(::num_threads_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)

## Thread 2

Thread 2 is the same as thread 1 except for returns.

Thread 2 total: 84

Total: 331
