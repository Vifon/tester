/* File: example.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tester.h"

void bubblesort_temp_var()
{
    int arr[16000];
    int i;
    for (i = 0; i < 16000; ++i) {
        arr[i] = rand();
    }

    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (i = 0; i < 16000-1; ++i) {
            if (arr[i] > arr[i+1]) {
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                sorted = 0;
            }
        }
    }
}

void bubblesort_xor_swap()
{
    int arr[16000];
    int i;
    for (i = 0; i < 16000; ++i) {
        arr[i] = rand();
    }

    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (i = 0; i < 16000-1; ++i) {
            if (arr[i] > arr[i+1]) {
                arr[i]   ^= arr[i+1];
                arr[i+1] ^= arr[i];
                arr[i]   ^= arr[i+1];
                sorted = 0;
            }
        }
    }
}

deftest(bubblesort)
{
    TIMER(bubblesort_temp_var());
    TIMER(bubblesort_xor_swap());

    END_TEST();
}

deftest(math)
{
    TEST(2 + 3 == 5);
    TEST(2 * 3 == 5);
    TEST(3 > 4);
    TEST(7 == 19);
    TEST(8 % 7 == 1);

    END_TEST();
}

deftest(string)
{
    TEST("abc"[2] == 'c');
    TEST("foo"+2 == &"foo"[2]);
    TEST("foo"+3 == &"foo"[2]);

    END_TEST();
}


deftest(test_suite)
{
    math();
    string();

    END_TEST();
}

deftest(timers)
{
    bubblesort();

    END_TEST();
}

int main(int argc, char *argv[])
{
    TEST_COLOR_INIT_AUTO();

    srand(time(0));

    return (test_suite() & timers()) == 0;
}
