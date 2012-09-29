NAME
====

tester - a simple testing framework for C/C++

SYNOPSIS
========

    #include "tester.h"

    deftest(name) { ... }
    void END_TEST();

    void TEST(predicate);
    void STEST(predicate);
    void TIMER(code);

    void TEST_COLOR_INIT(int turn_on);
    void TEST_COLOR_INIT_AUTO();    /* needs unistd.h */

Link with `-ltester`

INSTALLATION
============

Run `make` and then `make PREFIX=/your/prefix install`. The default prefix is `/usr/local`. Run `make example` to compile the example.

DESCRIPTION
===========

**TEST_COLOR_INIT** turns on all the pretty colors and whatnot when called with a non-zero argument.

**TEST_COLOR_INIT_AUTO** automatically turns on the coloring if stderr is an interactive terminal.

**deftest** macro defines a test-function in which you can use the other macros. You can use them in all the functions called from this function as long as they are not called from the outside. You *must* end it with END_TEST() macro! One deftest function *must not* call another. This test-function returns non-zero if all the tests passed.

**TEST** checks whether a given predicate is true.

**STEST** is the same as **TEST** but does not print anything on success. The 'S' stands for "silent".

**TIMER** measures the code execution time.

EXAMPLE
=======

    #include "tester.h"
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
        
        return mytest1() | mytest2();
    }

COPYRIGHT
=========

Copyright (C) 2012  Wojciech Siewierski

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
