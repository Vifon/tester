/* File: tester.c */

const char* _RED             = "";
const char* _RED_B           = "";
const char* _GREEN           = "";
const char* _GREEN_B         = "";
const char* _BLUE_B          = "";
const char* _MAGENTA_B       = "";
const char* _CYAN            = "";
const char* _CYAN_B          = "";
const char* _RESET           = "";

const char* _ELLIPSIS        = "";
const char* _REVERT_ELLIPSIS = "";

/********************************************************************/

int _tests_failed      = 0;
const char* _test_name = "UNDEF";

/********************************************************************/

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
