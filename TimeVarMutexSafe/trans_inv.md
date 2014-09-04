### Thread 0

3

    ..main():::ENTER
    ::inode == ::busy
    ::inode == ::block
    ::inode == 0
    ===========================================================================
    ..main():::EXIT
    ::inode == ::busy
    ::inode == ::block
    ::inode == 1

### Thread 1

3

    ..allocator():::ENTER
    ::inode == ::busy
    ::inode == ::block
    ::inode == 0
    ===========================================================================
    ..allocator():::EXIT
    ::inode == ::busy
    ::inode == ::block
    ::inode == 1

### Thread 2

3

    ..de_allocator():::ENTER
    ::inode == ::busy
    ::inode == ::block
    ::inode one of { 0, 1 }
    ===========================================================================
    ..de_allocator():::EXIT
    ::inode == ::busy
    ::inode == ::block
    ::inode one of { 0, 1 }
