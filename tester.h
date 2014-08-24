/* File: tester.h */
/**********************************************************************/
/* Copyright (C) 2012  Wojciech Siewierski                            */
/*                                                                    */
/* This program is free software, you can redistribute it and/or      */
/* modify it under the terms of the new-style BSD license.            */
/*                                                                    */
/* You should have received a copy of the BSD license along with this */
/* program. If not, see <http://www.debian.org/misc/bsd.license>.     */
/**********************************************************************/

#ifndef _h_TESTER_
#define _h_TESTER_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************/

/* these formatting strings are populated by TEST_COLOR_INIT */
extern const char* _red;
extern const char* _red_b;
extern const char* _green;
extern const char* _green_b;
extern const char* _blue_b;
extern const char* _magenta_b;
extern const char* _cyan;
extern const char* _cyan_b;
extern const char* _reset;

extern const char* _ellipsis;
extern const char* _revert_ellipsis;

/********************************************************************/

#define _test_max_nest_level 16

extern int _test_nest_level;
extern int _tests_failed[_test_max_nest_level];
extern const char* _test_name[_test_max_nest_level];

/********************************************************************/

/* turn on colors when `turn_on' is non-zero */
void TEST_COLOR_INIT(int turn_on);

/**************************************/

/* turn on colors if stderr is a tty or user started the program with --color
 * REQUIRES unistd.h*/
#define TEST_COLOR_INIT_AUTO()                                          \
    TEST_COLOR_INIT((argc > 1 && strcmp(argv[1], "--color") == 0) ||    \
                    isatty(fileno(stderr)));

/********************************************************************/

#define BEGIN_TEST(NAME)                                \
    do {                                                \
        _tests_failed[++_test_nest_level] = 0;          \
        _test_name[_test_nest_level] = #NAME;           \
    } while (0)

/**************************************/

/* defines a new test */
#define deftest(NAME)                           \
    int NAME()                                  \
    {                                           \
        BEGIN_TEST(NAME);

/**************************************/

#define declaretest(NAME) int NAME()
#define decltest declaretest

/********************************************************************/

void _tests_print_names();

/********************************************************************/

/* checks a given predicate */
#define TEST(P)                                               \
    do {                                                      \
        const char* _color = _green;                          \
        if (!(P)) {                                           \
            _color = _red_b;                                  \
            ++_tests_failed[_test_nest_level];                \
        }                                                     \
        _tests_print_names();                                 \
        fprintf(stderr,                                       \
                "%s%s%s:%s%3d%s:\t%s%s%s\n",                  \
                ""         , __FILE__   , _reset ,            \
                _blue_b    , __LINE__   , _reset ,            \
                _color     , #P         , _reset);            \
    } while (0)

/********************************************************************/

/* silent test - no output on success */
#define STEST(P)                                              \
    do {                                                      \
        if (!(P)) {                                           \
            ++_tests_failed[_test_nest_level];                \
            _tests_print_names();                             \
            fprintf(stderr,                                   \
                    "%s%s%s:%s%3d%s:\t%s%s%s\n",              \
                    ""         , __FILE__   , _reset ,        \
                    _blue_b    , __LINE__   , _reset ,        \
                    _red_b     , #P         , _reset);        \
        }                                                     \
    } while (0)

/********************************************************************/

#define CRIT_TEST(P)                                                    \
    do {                                                                \
        const char* _color = _green;                                    \
        int _this_failed = 0;                                           \
        if (!(P)) {                                                     \
            _color = _red_b;                                            \
            ++_tests_failed[_test_nest_level];                          \
            _this_failed = 1;                                           \
        }                                                               \
        _tests_print_names();                                           \
        fprintf(stderr,                                                 \
                "%s%s%s:%s%3d%s:\t%s%s%s\n",                            \
                ""         , __FILE__   , _reset ,                      \
                _this_failed ? _red_b : _blue_b ,                       \
                __LINE__   , _reset     ,                               \
                _color     , #P         , _reset);                      \
        if (_this_failed) {                                             \
            TEST_PASSED();                                              \
        }                                                               \
    } while (0)

/********************************************************************/

#define TIMER(P)                                                      \
    do {                                                              \
    _tests_print_names();                                             \
        fprintf(stderr,                                               \
                "%s%s%s:\t%s%s%s - %s",                               \
                ""         , __FILE__   , _reset ,                    \
                _cyan      , #P         , _reset ,                    \
                _ellipsis);                                           \
                                                                      \
        clock_t _timer_start = clock();                               \
        P;                                                            \
        float _timer_result = (float)(clock() - _timer_start)         \
                              / CLOCKS_PER_SEC;                       \
                                                                      \
        fprintf(stderr,                                               \
                "%s%s%gs%s\n",                                        \
                _revert_ellipsis,                                     \
                _cyan_b    , _timer_result , _reset);                 \
    } while (0)

/********************************************************************/

#define TEST_PASSED()                                                   \
    do {                                                                \
        _tests_print_names();                                           \
        if (_tests_failed[_test_nest_level] != 0) {                     \
            fprintf(stderr,                                             \
                    "%s%d%s %s%s%s\n",                                  \
                    _red_b , _tests_failed[_test_nest_level] , _reset , \
                    _red   , "tests failed"                  , _reset); \
        } else {                                                        \
            fprintf(stderr,                                             \
                    "%s%s%s\n",                                         \
                    _green_b   , "all tests passed" , _reset);          \
        };                                                              \
        int success = !_tests_failed[_test_nest_level--];               \
        if (_test_nest_level >= 0) {                                    \
            _tests_failed[_test_nest_level] += !success;                \
        }                                                               \
        return success;                                                 \
    } while (0)

/**************************************/

/* end of a deftest function */
#define END_TEST() TEST_PASSED();}

/********************************************************************/

int runtests(int(*test)(), ...);


#ifdef __cplusplus
}
#endif

#endif
