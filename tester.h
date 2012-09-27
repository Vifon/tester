// File: tester.h
#ifndef _TESTER_H_
#define _TESTER_H_

#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////

static const char* RED       = "";
static const char* RED_B     = "";
static const char* GREEN     = "";
static const char* GREEN_B   = "";
static const char* BLUE_B    = "";
static const char* MAGENTA_B = "";
static const char* RESET     = "";

//////////////////////////////////////////////////////////////////////

#define TEST_NAME_LENGTH 256

static int  _tests_failed = 0;
static char _test_name[TEST_NAME_LENGTH] = "UNDEF";

//////////////////////////////////////////////////////////////////////

/* turn on colors when `turn_on' is non-zero */
void TEST_COLOR_INIT(int turn_on)
{
    if (turn_on) {
        RED       = "\033[31m";
        RED_B     = "\033[31;1m";
        GREEN     = "\033[32m";
        GREEN_B   = "\033[32;1m";
        BLUE_B    = "\033[34;1m";
        MAGENTA_B = "\033[35;1m";
        RESET     = "\033[0m";
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
    BEGIN_TEST(NAME);                           \

//////////////////////////////////////////////////////////////////////

/* checks a given predicate */
#define TEST(P)                                               \
    do {                                                      \
        const char* _color = GREEN;                           \
        if (!(P)) {                                           \
            _color = RED_B;                                   \
            ++_tests_failed;                                  \
        }                                                     \
        fprintf(stderr,                                       \
                "%s%s%s: %s%s%s:%s%3d%s:\t%s%s%s\n",          \
                MAGENTA_B , _test_name , RESET ,              \
                ""        , __FILE__   , RESET ,              \
                BLUE_B    , __LINE__   , RESET ,              \
                _color    , #P         , RESET);              \
    } while (0)

//////////////////////////////////////////////////////////////////////

/* silent test - no output on success */
#define STEST(P)                                            \
    do {                                                    \
        if (!(P)) {                                         \
            ++_tests_failed;                                \
            fprintf(stderr,                                 \
                    "%s%s%s: %s%s%s:%s%3d%s:\t%s%s%s\n",    \
                    MAGENTA_B , _test_name , RESET ,        \
                    ""        , __FILE__   , RESET ,        \
                    BLUE_B    , __LINE__   , RESET ,        \
                    RED_B     , #P         , RESET);        \
        }                                                   \
    } while (0)

//////////////////////////////////////////////////////////////////////

#define TEST_PASSED()                                               \
    do {                                                            \
        if (_tests_failed != 0) {                                   \
            fprintf(stderr,                                         \
                    "%s%s%s: %s%d%s %s%s%s\n",                      \
                    MAGENTA_B , _test_name     , RESET ,            \
                    RED_B     , _tests_failed  , RESET ,            \
                    RED       , "tests failed" , RESET);            \
        } else {                                                    \
            fprintf(stderr,                                         \
                    "%s%s%s: %s%s%s\n",                             \
                    MAGENTA_B , _test_name         , RESET ,        \
                    GREEN_B   , "all tests passed" , RESET);        \
        };                                                          \
        return !!_tests_failed;                                     \
    } while (0)

////////////////////////////////////////

/* end of a deftest function */
#define END_TEST() TEST_PASSED();}

//////////////////////////////////////////////////////////////////////

#endif
