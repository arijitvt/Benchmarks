## Notes

### Incorrect Daikon Invariants

In the function `pqueue_get()`, `Daikon` incorrectly sees `n_files` only as 3.
It can actually be 2 or 3. This is caused by the interleaving of the `main`
thread with the `worker` thread(s). `main` is modifying `n_files` in
`foreach_path()` (called via `do_ftw()` and `ftw()`).

There are 3 incorrect invariants in `pqueue_get()`

Similarly, `n_files` can be 2 or 3 during the entry of `scan_file()`. Daikon
again incorrectly records it as 3.

There are 3 incorrect invariants in `scan_file()`.

The `n_files` issues is also found in the entry and exit of `worker()`. Daikon
thinks that it is equal to 3. This is not surprising; all of these invariants
are incorrect for the same reason.

There are 3 incorrect invariants in `worker()`

Overall, there are 9 incorrect daikon invariants.

### Daikon output

    ..bm_init():::ENTER
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == icase
    ::max_depth == ::maxlen
    ::rstr == x
    ::rlen == m
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    bmp has only one value
    bmp != null
    ::version > ::argv0
    ===========================================================================
    ..bm_init():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == return
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::debug == orig(icase)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::max_depth == orig(::maxlen)
    ::rstr == orig(::rstr)
    ::rstr == orig(x)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::nworkers == orig(::nworkers)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    ..deslash():::ENTER
    ::debug == ::rlen
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::max_depth == ::maxlen
    ::rstr == str
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::nworkers == 1
    ::n_bytes == 0
    ::version > ::argv0
    ===========================================================================
    ..deslash():::EXIT
    ::debug == ::rlen
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == orig(::debug)
    ::debug == orig(::rlen)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::max_depth == orig(::maxlen)
    ::rstr == orig(::rstr)
    ::rstr == orig(str)
    ::nworkers == orig(::nworkers)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::nworkers == 1
    ::n_bytes == 0
    return == 4
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    ..do_ftw():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_bytes == 0
    path == "dir"
    ::version > ::argv0
    ::version < path
    ::argv0 < path
    ===========================================================================
    ..do_ftw():::EXIT
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == return
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    ::version > ::argv0
    ::version == orig(::version)
    ::version < orig(path)
    ::argv0 == orig(::argv0)
    ::argv0 < orig(path)
    ===========================================================================
    ..foreach_path():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 0, 1, 2 }
    ::n_bytes one of { 0, 4096 }
    path one of { "dir", "dir/cool.mp3", "dir/file" }
    sp != null
    f one of { 0, 1 }
    ::version > ::argv0
    ::version < path
    ::debug <= ::n_files
    ::debug <= f
    ::argv0 < path
    ::max_depth > ::n_files
    ::max_depth > f
    ::rlen > ::n_files
    ::rlen > f
    ::nworkers >= f
    ::maxlen > ::n_files
    ::maxlen > f
    ::n_files != f
    ===========================================================================
    ..foreach_path():::EXIT
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == return
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 1, 2, 3 }
    ::n_bytes == 4096
    ::version > ::argv0
    ::version == orig(::version)
    ::version < orig(path)
    ::debug < ::n_files
    ::debug <= orig(::n_files)
    ::debug <= orig(f)
    ::argv0 == orig(::argv0)
    ::argv0 < orig(path)
    ::max_depth > ::n_files
    ::max_depth > orig(::n_files)
    ::max_depth > orig(f)
    ::rlen > ::n_files
    ::rlen > orig(::n_files)
    ::rlen > orig(f)
    ::nworkers <= ::n_files
    ::nworkers >= orig(f)
    ::maxlen > ::n_files
    ::maxlen > orig(::n_files)
    ::maxlen > orig(f)
    ::n_files > orig(::n_files)
    ::n_files >= orig(f)
    orig(f) % ::n_files == 0
    ::n_bytes >= orig(::n_bytes)
    ===========================================================================
    ..main():::ENTER
    ::debug == ::rlen
    ::debug == ::verbose
    ::debug == ::nworkers
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::max_depth == ::maxlen
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "pfscan"
    ::max_depth == 64
    ::rstr == null
    ::n_bytes == 0
    argc == 5
    argv has only one value
    argv != null
    ::version < ::argv0
    ===========================================================================
    ..main():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == return
    ::debug == orig(::debug)
    ::debug == orig(::rlen)
    ::debug == orig(::verbose)
    ::debug == orig(::nworkers)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::maxlen == orig(::max_depth)
    ::maxlen == orig(::maxlen)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    ::version > ::argv0
    ::version == orig(::version)
    ::version < orig(::argv0)
    ::argv0 < orig(::argv0)
    ===========================================================================
    ..pqueue_close():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    qp has only one value
    qp != null
    ::version > ::argv0
    ===========================================================================
    ..pqueue_close():::EXIT
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == orig(::n_files)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    ..pqueue_get():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    qp has only one value
    qp != null
    item has only one value
    item != null
    ::version > ::argv0
    ===========================================================================
    ..pqueue_get():::EXIT
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == orig(::n_files)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    return one of { 0, 1 }
    ::version > ::argv0
    ::version == orig(::version)
    ::debug <= return
    ::argv0 == orig(::argv0)
    ::max_depth > return
    ::rlen > return
    ::nworkers >= return
    ::maxlen > return
    ::n_files > return
    ===========================================================================
    ..pqueue_init():::ENTER
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_bytes == 0
    qp has only one value
    qp != null
    qsize == 9
    ::version > ::argv0
    ===========================================================================
    ..pqueue_init():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == return
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == orig(::nworkers)
    ::maxlen == orig(::maxlen)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_bytes == 0
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    ..pqueue_put():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 2, 3 }
    ::n_bytes == 4096
    qp has only one value
    qp != null
    item != null
    ::version > ::argv0
    ::debug < ::n_files
    ::max_depth > ::n_files
    ::rlen > ::n_files
    ::nworkers < ::n_files
    ::maxlen > ::n_files
    ===========================================================================
    ..pqueue_put():::EXIT
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == ::aworkers
    ::nworkers == return
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == orig(::n_files)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 2, 3 }
    ::n_bytes == 4096
    ::version > ::argv0
    ::version == orig(::version)
    ::debug < ::n_files
    ::argv0 == orig(::argv0)
    ::max_depth > ::n_files
    ::rlen > ::n_files
    ::nworkers < ::n_files
    ::maxlen > ::n_files
    ===========================================================================
    ..scan_file():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    pathname one of { "dir/cool.mp3", "dir/file" }
    ::version > ::argv0
    ::version < pathname
    ::argv0 < pathname
    ===========================================================================
    ..scan_file():::EXIT
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == orig(::n_files)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    return == -1
    ::version > ::argv0
    ::version == orig(::version)
    ::version < orig(pathname)
    ::argv0 == orig(::argv0)
    ::argv0 < orig(pathname)
    ===========================================================================
    ..worker():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    arg == null
    ::version > ::argv0
    ===========================================================================
    ..worker():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == orig(::n_files)
    ::n_bytes == orig(::n_bytes)
    return == orig(arg)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 1007
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    return == null
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    main.c.preBmBc():::ENTER
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::max_depth == ::maxlen
    ::rlen == m
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    x has only one value
    x != null
    bmBc has only one value
    bmBc != null
    ::version > ::argv0
    ===========================================================================
    main.c.preBmBc():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::max_depth == orig(::maxlen)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::nworkers == orig(::nworkers)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    main.c.preBmGs():::ENTER
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::max_depth == ::maxlen
    ::rlen == m
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    x has only one value
    x != null
    bmGs has only one value
    bmGs != null
    ::version > ::argv0
    ===========================================================================
    main.c.preBmGs():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == return
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::max_depth == orig(::maxlen)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::nworkers == orig(::nworkers)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ===========================================================================
    main.c.suffixes():::ENTER
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::max_depth == ::maxlen
    ::rlen == m
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    x has only one value
    x != null
    suff has only one value
    suff != null
    ::version > ::argv0
    ===========================================================================
    main.c.suffixes():::EXIT
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::max_depth == orig(::maxlen)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::nworkers == orig(::nworkers)
    ::n_bytes == orig(::n_bytes)
    ::version == "1.0"
    ::debug == 0
    ::argv0 == "./output"
    ::max_depth == 64
    ::rstr has only one value
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 0
    ::version > ::argv0
    ::version == orig(::version)
    ::argv0 == orig(::argv0)

