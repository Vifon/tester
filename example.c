/* File: example.c */
#include <stdio.h>
#include <unistd.h>
#include "tester.h"

void bubblesort()
{
    int arr[10240];
    int i;
    for (i = 0; i < 10240; ++i) {
        arr[i] = rand();
    }

    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (i = 0; i < 10240-1; ++i) {
            if (arr[i] > arr[i+1]) {
                arr[i]   ^= arr[i+1];
                arr[i+1] ^= arr[i];
                arr[i]   ^= arr[i+1];
                sorted = 0;
            }
        }
    }
}

deftest(math)
{
    TEST(2 + 3 == 5);
    TEST(2 * 3 == 5);
    TEST(-8 % 7 == -1);
    TIMER(bubblesort());

    END_TEST();
}

deftest(string)
{
    TEST("abc"[2] == 'c');
    TEST("abc"[2] == 2["abc"]);

    END_TEST();
}

deftest(another_test)
{
    TEST(0);
    TEST(0);
    STEST(0);
    STEST(1);

    END_TEST();
}

int main(int argc, char *argv[])
{
    TEST_COLOR_INIT_AUTO();

    srand(time(0));

    return math() | string() | another_test();
}
