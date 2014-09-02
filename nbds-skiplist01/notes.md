## Notes

Daikon fails to see all possible return values of `cas()` related functions

### `sl_cas()`

Daikon output:

    ..sl_cas():::EXIT
    ::num_threads_ == orig(::num_threads_)
    ::start_ == ::stop_
    ::start_ == ::load_
    ::start_ == ::get_range_
    ::start_ == ::put_range_
    ::start_ == ::duration_
    ::start_ == ::halt_
    ::start_ == orig(::start_)
    ::start_ == orig(::stop_)
    ::start_ == orig(::load_)
    ::start_ == orig(::get_range_)
    ::start_ == orig(::put_range_)
    ::start_ == orig(::duration_)
    ::start_ == orig(::halt_)
    ::sl_ == orig(::sl_)
    ::sl_ == orig(sl)
    ::num_keys_ == orig(::num_keys_)
    ::load_time_ == orig(::load_time_)
    ::rcu_ == orig(::rcu_)
    ::rcu_last_posted_ == orig(::rcu_last_posted_)
    ::pending_ == orig(::pending_)
    ::lwt_buf_ == orig(::lwt_buf_)
    ::num_threads_ == 1
    ::start_ == 0
    ::sl_ has only one value
    ::num_keys_ == 0
    ::load_time_ == 0.0
    ::rcu_ has only one value
    ::rcu_last_posted_ has only one value
    ::pending_ has only one value
    ::flags_ == ""
    ::lwt_buf_ has only one value
    return one of { 0, 100 }
    ::flags_ == ::flag_state_
    ::flags_ == orig(::flags_)
    ::flags_ == orig(::flag_state_)

The return value should be one of 0, 1, or 100. These are the cases when the
hashtable is empty, thread 2 went first and thread 1 went first respectively.

Both PCB and HaPSet capture this case
