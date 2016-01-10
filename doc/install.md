# Installing librsync {#page_install}

## Requirements

To build librsync you will need:

* A C compiler and appropriate headers and libraries

* [CMake]

* Make, or some other build tool supported by CMake

* [popt] command line parsing library

* [Doxygen] - optional, to build docs

[popt]: http://rpm5.org/files/popt/
[CMake]: http://cmake.org/
[Doxygen]: https://www.stack.nl/~dimitri/doxygen


## Building

Generate the Makefile by running

    $ cmake .

After building you can install `rdiff` and `librsync` for system-wide use.

    $ make
    
To run the tests:

    $ make test
    
(Note that [CMake will not automatically build before testing](https://github.com/librsync/librsync/issues/49).)

To install:

    $ sudo make install
    
To build the documentation:

    $ make doc

librsync should be widely portable. Patches to fix portability bugs are
welcome.

If you are using GNU libc, you might like to use

    MALLOC_CHECK_=2 ./rdiff

to detect some allocation bugs.

librsync has annotations for the SPLINT static checking tool.


## Build-Ninja

CMake generates input files for an underlying build tool that will actually do
the build. Typically this is Make, but others are supported. In particular
[Ninja] is a nice alternative. To use it:

    $ cmake -G Ninja .
    $ ninja all
    $ ninja test

[Ninja]: http://build-ninja.org


## Cygwin

With Cygwin you can build using gcc as under a normal unix system. It
is also possible to compile under Cygwin using MSVC++. You must have
environment variables needed by MSVC set using the Vcvars32.bat
script.