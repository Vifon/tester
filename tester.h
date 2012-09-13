// File: tester.h
#ifndef _TESTER_H_
#define _TESTER_H_

#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////

#define TEST_COLOR_LENGTH 16

static char RED[TEST_COLOR_LENGTH]       = "";
static char RED_B[TEST_COLOR_LENGTH]     = "";
static char GREEN[TEST_COLOR_LENGTH]     = "";
static char GREEN_B[TEST_COLOR_LENGTH]   = "";
static char BLUE_B[TEST_COLOR_LENGTH]    = "";
static char MAGENTA_B[TEST_COLOR_LENGTH] = "";
static char RESET[TEST_COLOR_LENGTH]     = "";

//////////////////////////////////////////////////////////////////////

#define TEST_NAME_LENGTH 256

static int  _tests_failed = 0;
static char _test_name[TEST_NAME_LENGTH] = "UNDEF";

//////////////////////////////////////////////////////////////////////

/* turn on colors when `turn_on' is non-zero */
void TEST_COLOR_INIT(int turn_on)
{
    if (turn_on) {
        strncpy(RED       , "[31m"   , TEST_COLOR_LENGTH);
        strncpy(RED_B     , "[1;31m" , TEST_COLOR_LENGTH);
        strncpy(GREEN     , "[32m"   , TEST_COLOR_LENGTH);
        strncpy(GREEN_B   , "[1;32m" , TEST_COLOR_LENGTH);
        strncpy(BLUE_B    , "[1;34m" , TEST_COLOR_LENGTH);
        strncpy(MAGENTA_B , "[1;35m" , TEST_COLOR_LENGTH);
        strncpy(RESET     , "[0m"    , TEST_COLOR_LENGTH);
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
