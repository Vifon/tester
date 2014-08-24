NAME
====

tester - a simple testing framework for C/C++

SYNOPSIS
========

```C
#include <tester.h>

deftest(name) { ... }
declaretest(name);
decltest(name);
void BEGIN_TEST(name);
void END_TEST();

void TEST(predicate);
void STEST(predicate);
void CRIR_TEST(predicate);
void TIMER(code);

void TEST_COLOR_INIT(int turn_on);
void TEST_COLOR_INIT_AUTO();    /* needs unistd.h */

int runtests(...);
```

Link with `-ltester`

INSTALLATION
============

Run `make` and then `make PREFIX=/your/prefix install`. The default prefix is `/usr/local`. Make sure that prefix is in your `LIBRARY_PATH` and `LD_LIBRARY_PATH`. Run `make example` to compile the example.

DESCRIPTION
===========

**TEST_COLOR_INIT** turns on all the pretty colors and whatnot when called with a non-zero argument.

**TEST_COLOR_INIT_AUTO** automatically turns on the coloring if stderr is an interactive terminal.

**deftest** macro defines a test-function in which you can use the other macros. You can use them in all the functions called from this function as long as they are not called from the outside. You *must* end it with END_TEST() macro! Since version 1.0, tests can be nested (up to 16 nest levels). A subtest with any failed tests counts as a single failed test in a test suite. Test suites return non-zero on success.

**BEGIN_TEST** called with the appropriate function name may be used at the beginning of a regular argumentless function returning int if you don't want to use **deftest**'s syntactic sugar.

**declaretest** creates a declaration of a deftest function for the headers.

**decltest** alias to **declaretest**

**TEST** checks whether a given predicate is true.

**STEST** is the same as **TEST** but does not print anything on success. The 'S' stands for "silent".

**CRIT_TEST** is the same as **TEST** but additionally aborts the current test suite.

**TIMER** measures the code execution time.

**runtests** runs a list of tests. The last test *must* be a NULL pointer. Returns non-zero if any test has failed. Zero means a success for this function result to be used as a program exitcode.

EXAMPLE
=======

```C
#include <tester.h>
#include <unistd.h>    /* for TEST_COLOR_INIT_AUTO */

deftest(mytest1)
{
    TEST(2 + 2 == 4);
    TEST(2 * 2 == 5);    /* will fail */
    
    END_TEST();
}

deftest(mytest2)
{
    TEST(some_stuff());
    
    END_TEST();
}

int main(int argc, char *argv[])
{
    TEST_COLOR_INIT_AUTO();
    
    return runtests(mytest1, mytest2, NULL);
}
```

COPYRIGHT
=========

Copyright (C) 2012  Wojciech Siewierski

This program is free software, you can redistribute it and/or
modify it under the terms of the new-style BSD license.

You should have received a copy of the BSD license along with this
program. If not, see <http://www.debian.org/misc/bsd.license>.
