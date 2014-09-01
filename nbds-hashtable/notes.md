## Notes

Author: Markus

Overall, daikon has two crucial missed invariants. It misses that thread 2
could run before thread 1 when adding items to the hash table. 

The majority of the invariants are generated about constants. For example,
variables such as `get_range_` are initially set by `main()` and remain
constant throughout the program.

## hti\_cas()

### Incorrect daikon invariants

Daikon incorrectly finds that the return of this function is either 0 or 100.
This indicates that the operation was always successful when there is a
possibility that it can be unsucessful. 

## ht\_cas()

### Incorrect daikon invariants
Daikon has the same problem with `ht_cas()` as `hti_cas()` (see above).

## Daikon output

The following is the full daikon output. The RTool + HaPSet results can be seen
in `rtool_res_hapset/`.

    ===========================================================================
    ..ht_alloc():::ENTER
    ::duration_ == ::halt_
    ::num_threads_ == 2
    ::ht_ == null
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::duration_ == 0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    key_type == null
    ::flags_ == ::flag_state_
    ===========================================================================
    ..ht_alloc():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == ::halt_
    ::duration_ == orig(::duration_)
    ::duration_ == orig(::halt_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ == null
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::duration_ == 0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    return has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..ht_cas():::ENTER
    ::ht_ == ht
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    key == 1
    expected_val == -2
    new_val one of { 1, 100 }
    ::flags_ == ::flag_state_
    ===========================================================================
    ..ht_cas():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::ht_ == orig(ht)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return one of { 0, 100 }
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..ht_count():::ENTER
    ::ht_ == ht
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..ht_count():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::ht_ == orig(ht)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return == 1
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..ht_free():::ENTER
    ::ht_ == ht
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..ht_free():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::ht_ == orig(ht)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..ht_print():::ENTER
    ::ht_ == ht
    ::halt_ == verbose
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..ht_print():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::ht_ == orig(ht)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::halt_ == orig(verbose)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..lwt_thread_init():::ENTER
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == thread_id
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..lwt_thread_init():::EXIT
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == orig(::num_threads_)
    ::num_threads_ == orig(::get_range_)
    ::num_threads_ == orig(::put_range_)
    ::num_threads_ == orig(::duration_)
    ::num_threads_ == orig(::halt_)
    ::num_threads_ == orig(thread_id)
    ::ht_ == orig(::ht_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..main():::ENTER
    ::num_threads_ == argc
    ::get_range_ == ::put_range_
    ::get_range_ == ::duration_
    ::get_range_ == ::halt_
    ::num_threads_ == 1
    ::ht_ == null
    ::get_range_ == 0
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    argv has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..main():::EXIT
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == return
    ::halt_ == orig(::get_range_)
    ::halt_ == orig(::put_range_)
    ::halt_ == orig(::duration_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..mem_init():::ENTER
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..mem_init():::EXIT
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == orig(::num_threads_)
    ::num_threads_ == orig(::get_range_)
    ::num_threads_ == orig(::put_range_)
    ::num_threads_ == orig(::duration_)
    ::num_threads_ == orig(::halt_)
    ::ht_ == orig(::ht_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..nbd_free():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    x has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..nbd_free():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..nbd_init():::ENTER
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..nbd_init():::EXIT
    ::ht_ == orig(::ht_)
    ::get_range_ == ::put_range_
    ::get_range_ == ::duration_
    ::get_range_ == ::halt_
    ::get_range_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::get_range_ == orig(::put_range_)
    ::get_range_ == orig(::duration_)
    ::get_range_ == orig(::halt_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 1
    ::ht_ == null
    ::get_range_ == 0
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..nbd_malloc():::ENTER
    ::duration_ == ::halt_
    ::num_threads_ one of { 0, 2 }
    ::ht_ == null
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::duration_ == 0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..nbd_malloc():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == ::halt_
    ::duration_ == orig(::duration_)
    ::duration_ == orig(::halt_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ one of { 0, 2 }
    ::ht_ == null
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::duration_ == 0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..rcu_defer_free():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..rcu_defer_free():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..rcu_thread_init():::ENTER
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == id
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..rcu_thread_init():::EXIT
    ::ht_ == orig(::ht_)
    ::get_range_ == ::put_range_
    ::get_range_ == ::duration_
    ::get_range_ == ::halt_
    ::get_range_ == orig(::num_threads_)
    ::get_range_ == orig(::get_range_)
    ::get_range_ == orig(::put_range_)
    ::get_range_ == orig(::duration_)
    ::get_range_ == orig(::halt_)
    ::get_range_ == orig(id)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 1
    ::ht_ == null
    ::get_range_ == 0
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..run_test():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    ..run_test():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return == 64
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..thread_1():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    unused == null
    ::flags_ == ::flag_state_
    ===========================================================================
    ..thread_1():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    return == orig(unused)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return == null
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    ..thread_2():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    unused == null
    ::flags_ == ::flag_state_
    ===========================================================================
    ..thread_2():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    return == orig(unused)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return == null
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.fifo_alloc():::ENTER
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    scale == 20
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.fifo_alloc():::EXIT
    ::num_threads_ == ::get_range_
    ::num_threads_ == ::put_range_
    ::num_threads_ == ::duration_
    ::num_threads_ == ::halt_
    ::num_threads_ == orig(::num_threads_)
    ::num_threads_ == orig(::get_range_)
    ::num_threads_ == orig(::put_range_)
    ::num_threads_ == orig(::duration_)
    ::num_threads_ == orig(::halt_)
    ::ht_ == orig(::ht_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 0
    ::ht_ == null
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    return has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.hti_alloc():::ENTER
    ::duration_ == ::halt_
    ::num_threads_ == 2
    ::ht_ == null
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::duration_ == 0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    parent has only one value
    scale == 4
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.hti_alloc():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == ::halt_
    ::duration_ == orig(::duration_)
    ::duration_ == orig(::halt_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ == null
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::duration_ == 0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    return has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.hti_cas():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    hti has only one value
    key == 1
    key_hash == 3121639372L
    expected == -2
    new one of { 1, 100 }
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.hti_cas():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return one of { 0, 100 }
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.hti_defer_free():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    hti has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.hti_defer_free():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.hti_lookup():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    hti has only one value
    key == 1
    key_hash == 3121639372L
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.hti_lookup():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.hti_release():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    hti has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.hti_release():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.lwt_trace():::ENTER
    ::num_threads_ one of { 0, 2 }
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::num_keys_ one of { 0, 4096 }
    ::load_time_ == 0.0
    ::duration_ one of { 0, 4 }
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::num_threads_ <= ::get_range_
    ::num_threads_ <= ::put_range_
    ::num_threads_ >= ::halt_
    ::get_range_ <= ::put_range_
    ::get_range_ >= ::duration_
    ::get_range_ >= ::halt_
    ::put_range_ >= ::duration_
    ::put_range_ >= ::halt_
    ::num_keys_ != value1
    ::duration_ >= ::halt_
    ::flags_ == ::flag_state_
    ::flags_ < flag
    ::flags_ < format
    flag < format
    value1 != value2
    ===========================================================================
    main.c.lwt_trace():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ one of { 0, 2 }
    ::get_range_ one of { 0, 943718 }
    ::put_range_ one of { 0, 996147 }
    ::num_keys_ one of { 0, 4096 }
    ::load_time_ == 0.0
    ::duration_ one of { 0, 4 }
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    ::num_threads_ <= ::get_range_
    ::num_threads_ <= ::put_range_
    ::num_threads_ >= ::halt_
    ::get_range_ <= ::put_range_
    ::get_range_ >= ::duration_
    ::get_range_ >= ::halt_
    ::put_range_ >= ::duration_
    ::put_range_ >= ::halt_
    ::num_keys_ != orig(value1)
    ::duration_ >= ::halt_
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ::flags_ < orig(flag)
    ::flags_ < orig(format)
    ===========================================================================
    main.c.murmur32_8b():::ENTER
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    key == 1
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.murmur32_8b():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == orig(::get_range_)
    ::put_range_ == orig(::put_range_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::duration_ == orig(::duration_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::halt_ == orig(::halt_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 2
    ::ht_ has only one value
    ::get_range_ == 943718
    ::put_range_ == 996147
    ::num_keys_ == 4096
    ::load_time_ == 0.0
    ::duration_ == 4
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::halt_ == 0
    ::lwt_buf_ has only one value
    return == 3121639372L
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)
    ===========================================================================
    main.c.rdtsc():::ENTER
    ::get_range_ == ::put_range_
    ::get_range_ == ::duration_
    ::get_range_ == ::halt_
    ::num_threads_ == 1
    ::ht_ == null
    ::get_range_ == 0
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    ::flags_ == ::flag_state_
    ===========================================================================
    main.c.rdtsc():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::ht_ == orig(::ht_)
    ::get_range_ == ::put_range_
    ::get_range_ == ::duration_
    ::get_range_ == ::halt_
    ::get_range_ == orig(::get_range_)
    ::get_range_ == orig(::put_range_)
    ::get_range_ == orig(::duration_)
    ::get_range_ == orig(::halt_)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 1
    ::ht_ == null
    ::get_range_ == 0
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    return == 27
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)

