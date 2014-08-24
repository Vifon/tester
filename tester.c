/* File: tester.c */
/**********************************************************************/
/* Copyright (C) 2012  Wojciech Siewierski                            */
/*                                                                    */
/* This program is free software, you can redistribute it and/or      */
/* modify it under the terms of the new-style BSD license.            */
/*                                                                    */
/* You should have received a copy of the BSD license along with this */
/* program. If not, see <http://www.debian.org/misc/bsd.license>.     */
/**********************************************************************/

#include "tester.h"

const char* _red             = "";
const char* _red_b           = "";
const char* _green           = "";
const char* _green_b         = "";
const char* _blue_b          = "";
const char* _magenta_b       = "";
const char* _cyan            = "";
const char* _cyan_b          = "";
const char* _reset           = "";

const char* _ellipsis        = "";
const char* _revert_ellipsis = "";

/********************************************************************/

int _test_nest_level = -1;
int _tests_failed[_test_max_nest_level] = {0,0,0};
const char* _test_name[_test_max_nest_level] = {"UNDEF", "UNDEF", "UNDEF"};

/********************************************************************/

void TEST_COLOR_INIT(int turn_on)
{
    if (turn_on) {
        _red       = "\033[31m";
        _red_b     = "\033[31;1m";
        _green     = "\033[32m";
        _green_b   = "\033[32;1m";
        _blue_b    = "\033[34;1m";
        _magenta_b = "\033[35;1m";
        _cyan      = "\033[36m";
        _cyan_b    = "\033[36;1m";
        _reset     = "\033[0m";

        _ellipsis        = "...";
        _revert_ellipsis = "\033[3D\033[0K";
    }
}

/********************************************************************/

void _tests_print_names()
{
    fputs(_magenta_b, stderr);
    int i;
    for (i = 0; i <= _test_nest_level; ++i) {
        fprintf(stderr, "%s : ", _test_name[i]);
    }
    fputs(_reset, stderr);
}

/********************************************************************/

int runtests(int(*test)(), ...)
{
    va_list ap;
    va_start(ap, test);
    int exitcode = 1;
    while (test != NULL) {
        exitcode &= test();
        test = va_arg(ap, int(*)());
    }
    va_end(ap);
    return !exitcode;
}
