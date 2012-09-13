/* File: example.c */
#include <stdio.h>
#include <unistd.h>
#include "tester.h"

deftest(math)
{
    TEST(5 == 2 + 3);
    TEST(5 == 2 * 3);
    TEST(-8 % 7 == -1);

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
    TEST(0);

    END_TEST();
}

int main(int argc, char *argv[])
{
    TEST_COLOR_INIT_AUTO();

    return math() | string() | another_test();
}
