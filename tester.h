// File: tester.h
#ifndef _TESTER_H_
#define _TESTER_H_

#include <stdio.h>
#include <string.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////

/* these formatting strings are populated by TEST_COLOR_INIT */
static const char* _RED       = "";
static const char* _RED_B     = "";
static const char* _GREEN     = "";
static const char* _GREEN_B   = "";
static const char* _BLUE_B    = "";
static const char* _MAGENTA_B = "";
static const char* _CYAN      = "";
static const char* _CYAN_B    = "";
static const char* _RESET     = "";

static const char* _ELLIPSIS        = "";
static const char* _REVERT_ELLIPSIS = "";

//////////////////////////////////////////////////////////////////////

#define TEST_NAME_LENGTH 256

static int  _tests_failed = 0;
static char _test_name[TEST_NAME_LENGTH] = "UNDEF";

//////////////////////////////////////////////////////////////////////

/* turn on colors when `turn_on' is non-zero */
void TEST_COLOR_INIT(int turn_on)
{
    if (turn_on) {
        _RED       = "\033[31m";
        _RED_B     = "\033[31;1m";
        _GREEN     = "\033[32m";
        _GREEN_B   = "\033[32;1m";
        _BLUE_B    = "\033[34;1m";
        _MAGENTA_B = "\033[35;1m";
        _CYAN      = "\033[36m";
        _CYAN_B    = "\033[36;1m";
        _RESET     = "\033[0m";

        _ELLIPSIS        = "...";
        _REVERT_ELLIPSIS = "\033[3D\033[0K";
    }
}

////////////////////////////////////////

/* turn on colors if stderr is a tty or user started the program with --color
 * REQUIRES unistd.h*/
#define TEST_COLOR_INIT_AUTO()                                          \
    TEST_COLOR_INIT((argc > 1 && strcmp(argv[1], "--color") == 0) ||    \
                    isatty(fileno(stderr)));


//////////////////////////////////////////////////////////////////////

#define BEGIN_TEST(NAME)                                \
    do {                                                \
        strncpy(_test_name, #NAME, TEST_NAME_LENGTH);   \
        _test_name[TEST_NAME_LENGTH-1] = '\0';          \
        _tests_failed = 0;                              \
    } while (0)

////////////////////////////////////////

/* defines a new test */
#define deftest(NAME)                           \
    int NAME()                                  \
    {                                           \
        BEGIN_TEST(NAME);                       \

//////////////////////////////////////////////////////////////////////

/* checks a given predicate */
#define TEST(P)                                               \
    do {                                                      \
        const char* _color = _GREEN;                          \
        if (!(P)) {                                           \
            _color = _RED_B;                                  \
            ++_tests_failed;                                  \
        }                                                     \
        fprintf(stderr,                                       \
                "%s%s%s: %s%s%s:%s%3d%s:\t%s%s%s\n",          \
                _MAGENTA_B , _test_name , _RESET ,            \
                ""         , __FILE__   , _RESET ,            \
                _BLUE_B    , __LINE__   , _RESET ,            \
                _color     , #P         , _RESET);            \
    } while (0)

//////////////////////////////////////////////////////////////////////

/* silent test - no output on success */
#define STEST(P)                                              \
    do {                                                      \
        if (!(P)) {                                           \
            ++_tests_failed;                                  \
            fprintf(stderr,                                   \
                    "%s%s%s: %s%s%s:%s%3d%s:\t%s%s%s\n",      \
                    _MAGENTA_B , _test_name , _RESET ,        \
                    ""         , __FILE__   , _RESET ,        \
                    _BLUE_B    , __LINE__   , _RESET ,        \
                    _RED_B     , #P         , _RESET);        \
        }                                                     \
    } while (0)

//////////////////////////////////////////////////////////////////////

#define TIMER(P)                                                      \
    do {                                                              \
        clock_t _timer_start = clock();                               \
        fprintf(stderr,                                               \
                "%s%s%s: %s%s%s:%s%3d%s:\t%s%s%s - %s",               \
            _MAGENTA_B , _test_name , _RESET ,                        \
            ""         , __FILE__   , _RESET ,                        \
            _BLUE_B    , __LINE__   , _RESET ,                        \
            _CYAN      , #P         , _RESET ,                        \
            _ELLIPSIS);                                               \
                                                                      \
        P;                                                            \
        float _timer_result = (float)(clock() - _timer_start)         \
                              / CLOCKS_PER_SEC;                       \
                                                                      \
        fprintf(stderr,                                               \
                "%s%s%gs%s\n",                                        \
                _REVERT_ELLIPSIS,                                     \
                _CYAN_B    , _timer_result , _RESET);                 \
    } while (0)

//////////////////////////////////////////////////////////////////////

#define TEST_PASSED()                                                 \
    do {                                                              \
        if (_tests_failed != 0) {                                     \
            fprintf(stderr,                                           \
                    "%s%s%s: %s%d%s %s%s%s\n",                        \
                    _MAGENTA_B , _test_name     , _RESET ,            \
                    _RED_B     , _tests_failed  , _RESET ,            \
                    _RED       , "tests failed" , _RESET);            \
        } else {                                                      \
            fprintf(stderr,                                           \
                    "%s%s%s: %s%s%s\n",                               \
                    _MAGENTA_B , _test_name         , _RESET ,        \
                    _GREEN_B   , "all tests passed" , _RESET);        \
        };                                                            \
        return !!_tests_failed;                                       \
    } while (0)

////////////////////////////////////////

/* end of a deftest function */
#define END_TEST() TEST_PASSED();}

//////////////////////////////////////////////////////////////////////

#endif
