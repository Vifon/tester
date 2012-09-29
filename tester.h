/* File: tester.h */
#ifndef _TESTER_H_
#define _TESTER_H_

#include <stdio.h>
#include <string.h>
#include <time.h>

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

extern int _tests_failed;
extern const char* _test_name;

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
        _tests_failed = 0;                              \
        _test_name    = #NAME;                          \
    } while (0)

/**************************************/

/* defines a new test */
#define deftest(NAME)                           \
    int NAME()                                  \
    {                                           \
        BEGIN_TEST(NAME);

/********************************************************************/

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

/********************************************************************/

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

/********************************************************************/

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

/********************************************************************/

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

/**************************************/

/* end of a deftest function */
#define END_TEST() TEST_PASSED();}

/********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
