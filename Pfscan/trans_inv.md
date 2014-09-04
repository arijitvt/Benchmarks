## Thread 0

16

    ..bm_init():::ENTER
    ::max_depth == ::maxlen
    ::rstr == x
    ::rlen == m
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::debug == icase
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 64
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    bmp has only one value
    bmp != null
    ===========================================================================
    ..bm_init():::EXIT
    ::rstr == orig(::rstr)
    ::max_depth == orig(::max_depth)
    ::max_depth == ::maxlen
    ::rlen == orig(::rlen)
    ::debug == orig(::debug)
    ::debug == orig(::verbose)
    ::debug == orig(::aworkers)
    ::debug == orig(::line_f)
    ::debug == orig(::ignore_case)
    ::debug == orig(::n_matches)
    ::debug == orig(::n_files)
    ::debug == orig(::n_bytes)
    ::debug == orig(icase)
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::nworkers == orig(::nworkers)
    ===========================================================================

15
    ..deslash():::ENTER
    ::max_depth == ::maxlen
    ::rstr == str
    ::rlen == ::debug
    ::rlen == ::verbose
    ::rlen == ::aworkers
    ::rlen == ::line_f
    ::rlen == ::ignore_case
    ::rlen == ::n_matches
    ::rlen == ::n_files
    ::rlen == ::n_bytes
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 64
    ::rstr != null
    ::rlen == 0
    ::nworkers == 1
    ===========================================================================
    ..deslash():::EXIT
    ::rstr == orig(::rstr)
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::rlen == orig(::rlen)
    ::rlen == ::debug
    ::rlen == ::verbose
    ::rlen == ::aworkers
    ::rlen == ::line_f
    ::rlen == ::ignore_case
    ::rlen == ::n_matches
    ::rlen == ::n_files
    ::rlen == ::n_bytes
    ::nworkers == orig(::nworkers)
    ===========================================================================

16

    ..do_ftw():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    path != null
    ===========================================================================
    ..do_ftw():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == return
    ::debug == orig(::debug)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::n_files == 3
    ::maxlen == orig(::maxlen)
    ::n_bytes == 4096
    ===========================================================================

16

    ..foreach_path():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 0, 1, 2 }
    ::n_bytes one of { 0, 4096 }
    path != null
    sp != null
    f one of { 0, 1 }
    ::max_depth > ::n_files
    ::max_depth != ::n_bytes
    ::max_depth > f
    ::rlen > ::n_files
    ::rlen != ::n_bytes
    ::rlen > f
    ::debug <= ::n_files
    ::debug <= ::n_bytes
    ::debug <= f
    ::nworkers != ::n_bytes
    ::nworkers >= f
    ::maxlen > ::n_files
    ::maxlen != ::n_bytes
    ::maxlen > f
    ::n_files <= ::n_bytes
    ::n_files != f
    ::n_bytes != f
    ===========================================================================
    ..foreach_path():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == orig(::debug)
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::maxlen == orig(::maxlen)
    ::nworkers == 1
    ::n_files one of { 1, 2, 3 }
    ::n_bytes == 4096
    ===========================================================================

15

    ..main():::ENTER
    ::max_depth == ::maxlen
    ::rlen == ::debug
    ::rlen == ::verbose
    ::rlen == ::nworkers
    ::rlen == ::aworkers
    ::rlen == ::line_f
    ::rlen == ::ignore_case
    ::rlen == ::n_matches
    ::rlen == ::n_files
    ::rlen == ::n_bytes
    ::version has only one value
    ::version != null
    ::argv0 has only one value
    ::argv0 != null
    ::max_depth == 64
    ::rstr == null
    ::rlen == 0
    argc == 5
    argv != null
    ===========================================================================
    ..main():::EXIT
    ::n_files == 3
    ::version == orig(::version)
    ::debug == 0
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::maxlen == orig(::maxlen)
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::nworkers == 1
    ::n_bytes == 4096
    ===========================================================================

15

    ..pqueue_close():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    ::n_files == 3
    ::n_bytes == 4096
    qp has only one value
    qp != null
    ===========================================================================
    ..pqueue_close():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == orig(::debug)
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == orig(::n_files)
    ::n_bytes == orig(::n_bytes)
    ===========================================================================

16

    ..pqueue_init():::ENTER
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    qp has only one value
    qp != null
    qsize == 9
    ===========================================================================
    ..pqueue_init():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::debug == return
    ::debug == orig(::debug)
    ::nworkers == orig(::nworkers)
    ::maxlen == orig(::maxlen)
    ===========================================================================

16

    ..pqueue_put():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 2, 3 }
    ::n_bytes == 4096
    qp has only one value
    qp != null
    item != null
    ::max_depth > ::n_files
    ::rlen > ::n_files
    ::debug < ::n_files
    ::nworkers < ::n_files
    ::maxlen > ::n_files
    ::n_files < ::n_bytes
    ===========================================================================
    ..pqueue_put():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == 0
    ::nworkers == ::aworkers
    ::nworkers == return
    ::nworkers == orig(::nworkers)
    ::maxlen == orig(::maxlen)
    ::n_bytes == orig(::n_bytes)
    ::n_files one of { 2, 3 }

16

    ===========================================================================
    ..preBmBc():::ENTER
    ::max_depth == ::maxlen
    ::rlen == m
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 64
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    x != null
    bmBc has only one value
    bmBc != null
    ===========================================================================
    ..preBmBc():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == ::maxlen
    ::max_depth == orig(::maxlen)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::debug == orig(::debug)
    ::nworkers == orig(::nworkers)

16

    ===========================================================================
    ..preBmGs():::ENTER
    ::max_depth == ::maxlen
    ::rlen == m
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 64
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    x != null
    bmGs != null
    ===========================================================================
    ..preBmGs():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::debug == orig(::debug)
    ::nworkers == orig(::nworkers)
    ===========================================================================

16

    ..suffixes():::ENTER
    ::max_depth == ::maxlen
    ::rlen == m
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 64
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    x != null
    suff != null
    ===========================================================================
    ..suffixes():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == ::maxlen
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::rlen == orig(m)
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == ::n_files
    ::debug == ::n_bytes
    ::debug == orig(::debug)
    ::nworkers == orig(::nworkers)

## Thread 1

16

    ..pqueue_get():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 0, 2, 3 }
    ::n_bytes one of { 0, 4096 }
    qp has only one value
    qp != null
    item != null
    ::max_depth > ::n_files
    ::max_depth != ::n_bytes
    ::rlen > ::n_files
    ::rlen != ::n_bytes
    ::debug <= ::n_files
    ::debug <= ::n_bytes
    ::nworkers != ::n_files
    ::nworkers != ::n_bytes
    ::maxlen > ::n_files
    ::maxlen != ::n_bytes
    ::n_files <= ::n_bytes
    ===========================================================================
    ..pqueue_get():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::nworkers == ::aworkers
    ::nworkers == orig(::nworkers)
    ::maxlen == orig(::maxlen)
    ::nworkers == 1
    ::n_files one of { 2, 3 }
    ::n_bytes == 4096
    ===========================================================================

16

    ..scan_file():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    ::n_files one of { 2, 3 }
    ::n_bytes == 4096
    pathname != null
    ::max_depth > ::n_files
    ::rlen > ::n_files
    ::debug < ::n_files
    ::nworkers < ::n_files
    ::maxlen > ::n_files
    ::n_files < ::n_bytes
    ===========================================================================
    ..scan_file():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::nworkers == ::aworkers
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_bytes == orig(::n_bytes)
    ::maxlen == 64
    ::n_files == 3
    ===========================================================================

16

    ..worker():::ENTER
    ::debug == ::verbose
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::nworkers == ::aworkers
    ::version has only one value
    ::version != null
    ::argv0 != null
    ::max_depth == 4079
    ::rstr != null
    ::rlen == 4
    ::debug == 0
    ::nworkers == 1
    ::maxlen == 64
    ::n_files >= 0
    ::n_bytes one of { 0, 4096 }
    arg == null
    ::max_depth > ::n_files
    ::max_depth != ::n_bytes
    ::rlen > ::n_files
    ::rlen != ::n_bytes
    ::debug <= ::n_files
    ::debug <= ::n_bytes
    ::nworkers != ::n_bytes
    ::maxlen > ::n_files
    ::maxlen != ::n_bytes
    ::n_files <= ::n_bytes
    ===========================================================================
    ..worker():::EXIT
    ::version == orig(::version)
    ::argv0 == orig(::argv0)
    ::max_depth == orig(::max_depth)
    ::rstr == orig(::rstr)
    ::rlen == orig(::rlen)
    ::debug == ::verbose
    ::debug == ::aworkers
    ::debug == ::line_f
    ::debug == ::ignore_case
    ::debug == ::n_matches
    ::debug == orig(::debug)
    ::nworkers == orig(::nworkers)
    ::nworkers == orig(::aworkers)
    ::maxlen == orig(::maxlen)
    ::n_files == 3
    ::n_bytes == 4096

Total: 221
