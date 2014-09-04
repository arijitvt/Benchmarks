
### Thread 0

19

    ..fifo_alloc():::ENTER
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::load_time_ == 0.0
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    scale == 20
    ===========================================================================
    ..fifo_alloc():::EXIT
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::load_time_ == orig(::load_time_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..ht_alloc():::ENTER
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == key_type
    ::num_keys_ == 0
    ::ht_ == null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::load_time_ == 0.0
    ::pending_ != null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..ht_alloc():::EXIT
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::load_time_ == orig(::load_time_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..ht_count():::ENTER
    ::ht_ == ht
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..ht_count():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ===========================================================================

19
    ..ht_free():::ENTER
    ::ht_ == ht
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..ht_free():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ===========================================================================

19
    ..ht_print():::ENTER
    ::ht_ == ht
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == verbose
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..ht_print():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::ht_ == orig(ht)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::tid_ == orig(::rx_)
    ::tid_ == orig(::ry_)
    ::tid_ == orig(::rz_)
    ::tid_ == orig(::rc_)
    ::tid_ == orig(::halt_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::rcu_ == orig(::rcu_last_posted_)
    ::rcu_ == orig(::flag_state_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================

19

    ..hti_alloc():::ENTER
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::load_time_ == 0.0
    ::pending_ != null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    parent != null
    scale == 4
    ===========================================================================
    ..hti_alloc():::EXIT
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::load_time_ == orig(::load_time_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..hti_defer_free():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    hti != null
    ===========================================================================
    ..hti_defer_free():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..hti_release():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    hti != null
    ===========================================================================
    ..hti_release():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..lwt_thread_init():::ENTER
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == thread_id
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::lwt_buf_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::load_time_ == 0.0
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..lwt_thread_init():::EXIT
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::load_time_ == orig(::load_time_)
    ::flags_ == orig(::flags_)
    ===========================================================================

16

    ..lwt_trace():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ one of { 0, 4096 }
    ::num_threads_ one of { 0, 2 }
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::duration_ one of { 0, 4 }
    ::load_time_ == 0.0
    ::tid_ == 0
    ::rcu_ == null
    ::flags_ has only one value
    ::flags_ != null
    flag != null
    format != null
    value2 one of { 0, 1 }
    ::num_keys_ <= ::get_range_
    ::num_keys_ <= ::put_range_
    ::num_keys_ >= ::duration_
    ::num_keys_ >= ::tid_
    ::num_keys_ < value1
    ::num_keys_ >= value2
    ::num_threads_ <= ::get_range_
    ::num_threads_ <= ::put_range_
    ::num_threads_ >= ::tid_
    ::num_threads_ < value1
    ::num_threads_ >= value2
    ::get_range_ <= ::put_range_
    ::get_range_ >= ::duration_
    ::get_range_ >= ::tid_
    ::get_range_ != value1
    ::get_range_ >= value2
    ::put_range_ >= ::duration_
    ::put_range_ >= ::tid_
    ::put_range_ != value1
    ::put_range_ >= value2
    ::duration_ >= ::tid_
    ::duration_ < value1
    ::duration_ >= value2
    ::tid_ < value1
    ::tid_ <= value2
    value1 > value2
    ===========================================================================
    ..lwt_trace():::EXIT
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::flags_ == orig(::flags_)
    ::num_keys_ one of { 0, 4096 }
    ::num_threads_ one of { 0, 2 }
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::duration_ one of { 0, 4 }
    ===========================================================================

19

    ..main():::ENTER
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::num_threads_ == argc
    ::num_keys_ == 0
    ::ht_ == null
    ::num_threads_ == 1
    ::load_time_ == 0.0
    ::pending_ != null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    argv != null
    ===========================================================================
    ..main():::EXIT
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == 0
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::ht_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ===========================================================================

19

    ..mem_init():::ENTER
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::lwt_buf_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::load_time_ == 0.0
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..mem_init():::EXIT
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::lwt_buf_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::load_time_ == orig(::load_time_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..nbd_free():::ENTER
    ::ht_ == x
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..nbd_free():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..nbd_init():::ENTER
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::lwt_buf_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::load_time_ == 0.0
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..nbd_init():::EXIT
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::load_time_ == orig(::load_time_)
    ::flags_ == orig(::flags_)
    ::num_threads_ == 1
    ::pending_ != null
    ::lwt_buf_ != null
    ===========================================================================

18

    ..nbd_malloc():::ENTER
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::num_threads_ one of { 0, 2 }
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::load_time_ == 0.0
    ::flags_ has only one value
    ::flags_ != null
    ::num_keys_ <= ::num_threads_
    ::num_keys_ <= ::get_range_
    ::num_keys_ <= ::put_range_
    ::num_keys_ < n
    ::num_threads_ <= ::get_range_
    ::num_threads_ <= ::put_range_
    ::num_threads_ < n
    ::get_range_ <= ::put_range_
    ::get_range_ != n
    ::put_range_ != n
    ===========================================================================
    ..nbd_malloc():::EXIT
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::load_time_ == orig(::load_time_)
    ::flags_ == orig(::flags_)
    ::num_threads_ one of { 0, 2 }
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::load_time_ == 0.0
    ===========================================================================

19

    ..rcu_defer_free():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    x != null
    ===========================================================================
    ..rcu_defer_free():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..rcu_thread_init():::ENTER
    ::num_keys_ == ::num_threads_
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == id
    ::ht_ == ::pending_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::load_time_ == 0.0
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..rcu_thread_init():::EXIT
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::num_keys_ == orig(id)
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::load_time_ == orig(::load_time_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..rdtsc():::ENTER
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::num_keys_ == 0
    ::ht_ == null
    ::num_threads_ == 1
    ::load_time_ == 0.0
    ::pending_ != null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..rdtsc():::EXIT
    ::num_keys_ == ::get_range_
    ::num_keys_ == ::put_range_
    ::num_keys_ == ::duration_
    ::num_keys_ == ::tid_
    ::num_keys_ == ::rx_
    ::num_keys_ == ::ry_
    ::num_keys_ == ::rz_
    ::num_keys_ == ::rc_
    ::num_keys_ == ::halt_
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == ::rcu_
    ::ht_ == ::rcu_last_posted_
    ::ht_ == ::flag_state_
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::load_time_ == orig(::load_time_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..run_test():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..run_test():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)

### Thread 1

19

    ..ht_cas():::ENTER
    ::ht_ == ht
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    key == 1
    expected_val == -2
    new_val == 100
    ===========================================================================
    ..ht_cas():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..hti_cas():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    hti != null
    key == 1
    key_hash == -1173327924
    expected == -2
    new == 100
    ===========================================================================
    ..hti_cas():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..hti_lookup():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    hti != null
    key == 1
    key_hash == -1173327924
    is_empty != null
    ===========================================================================
    ..hti_lookup():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 4096
    ::rcu_ == null
    ===========================================================================

19

    ..lwt_trace():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    flag != null
    format != null
    ::num_keys_ != value1
    ::num_keys_ != value2
    ::num_threads_ != value1
    ::num_threads_ != value2
    ::get_range_ != value1
    ::get_range_ != value2
    ::put_range_ != value1
    ::put_range_ != value2
    ::duration_ != value1
    ::duration_ != value2
    value1 != value2
    ===========================================================================
    ..lwt_trace():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ::num_keys_ == 4096
    ::rcu_ == null

19

    ===========================================================================
    ..murmur32_8b():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    key == 1
    ===========================================================================
    ..murmur32_8b():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)
    ===========================================================================

19

    ..thread_1():::ENTER
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == unused
    ::num_keys_ == 4096
    ::ht_ != null
    ::num_threads_ == 2
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::duration_ == 4
    ::load_time_ == 0.0
    ::tid_ == 0
    ::pending_ != null
    ::rcu_ == null
    ::lwt_buf_ != null
    ::flags_ has only one value
    ::flags_ != null
    ===========================================================================
    ..thread_1():::EXIT
    ::num_keys_ == orig(::num_keys_)
    ::ht_ == orig(::ht_)
    ::num_threads_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::duration_ == orig(::duration_)
    ::load_time_ == orig(::load_time_)
    ::tid_ == ::rx_
    ::tid_ == ::ry_
    ::tid_ == ::rz_
    ::tid_ == ::rc_
    ::tid_ == ::halt_
    ::tid_ == orig(::tid_)
    ::pending_ == orig(::pending_)
    ::rcu_ == ::rcu_last_posted_
    ::rcu_ == ::flag_state_
    ::rcu_ == return
    ::rcu_ == orig(::rcu_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::flags_ == orig(::flags_)

### Thread 2

Thread 1 is the same as thread 2 except for the return values

Thread 2 total: 114

Total: 645
