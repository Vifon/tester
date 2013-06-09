/* File: tester.h */
/*************************************************************************/
/* Copyright (C) 2012  Wojciech Siewierski                               */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef _TESTER_H_
#define _TESTER_H_

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
extern const char* _RED;
extern const char* _RED_B;
extern const char* _GREEN;
extern const char* _GREEN_B;
extern const char* _BLUE_B;
extern const char* _MAGENTA_B;
extern const char* _CYAN;
extern const char* _CYAN_B;
extern const char* _RESET;

extern const char* _ELLIPSIS;
extern const char* _REVERT_ELLIPSIS;

/********************************************************************/

#define _TEST_MAX_NEST_LEVEL 16

extern int _test_nest_level;
extern int _tests_failed[_TEST_MAX_NEST_LEVEL];
extern const char* _test_name[_TEST_MAX_NEST_LEVEL];

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
        const char* _color = _GREEN;                          \
        if (!(P)) {                                           \
            _color = _RED_B;                                  \
            ++_tests_failed[_test_nest_level];                \
        }                                                     \
        _tests_print_names();                                 \
        fprintf(stderr,                                       \
                "%s%s%s:%s%3d%s:\t%s%s%s\n",                  \
                ""         , __FILE__   , _RESET ,            \
                _BLUE_B    , __LINE__   , _RESET ,            \
                _color     , #P         , _RESET);            \
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
                    ""         , __FILE__   , _RESET ,        \
                    _BLUE_B    , __LINE__   , _RESET ,        \
                    _RED_B     , #P         , _RESET);        \
        }                                                     \
    } while (0)

/********************************************************************/

#define TIMER(P)                                                      \
    do {                                                              \
    _tests_print_names();                                             \
        fprintf(stderr,                                               \
                "%s%s%s:\t%s%s%s - %s",                               \
                ""         , __FILE__   , _RESET ,                    \
                _CYAN      , #P         , _RESET ,                    \
                _ELLIPSIS);                                           \
                                                                      \
        clock_t _timer_start = clock();                               \
        P;                                                            \
        float _timer_result = (float)(clock() - _timer_start)         \
                              / CLOCKS_PER_SEC;                       \
                                                                      \
        fprintf(stderr,                                               \
                "%s%s%gs%s\n",                                        \
                _REVERT_ELLIPSIS,                                     \
                _CYAN_B    , _timer_result , _RESET);                 \
    } while (0)

/********************************************************************/

#define TEST_PASSED()                                                   \
    do {                                                                \
        _tests_print_names();                                           \
        if (_tests_failed[_test_nest_level] != 0) {                     \
            fprintf(stderr,                                             \
                    "%s%d%s %s%s%s\n",                                  \
                    _RED_B , _tests_failed[_test_nest_level] , _RESET , \
                    _RED   , "tests failed"                  , _RESET); \
        } else {                                                        \
            fprintf(stderr,                                             \
                    "%s%s%s\n",                                         \
                    _GREEN_B   , "all tests passed" , _RESET);          \
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

#ifdef __cplusplus
}
#endif

#endif
