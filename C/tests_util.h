#ifndef tests_util_h
#define tests_util_h

#include <stdio.h>

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"
#define GREEN_ON "\033[32m"
#define COLOR_OFF "\033[m"


static int failed_tests = 0;

static void assert_test(int expr, const char* func_name, int line) 
{
    if (expr) 
    {
        printf(RED_ON "X Failed Test " BOLD_ON "%s" BOLD_OFF RED_ON". Line: " BOLD_ON "%d\n" BOLD_OFF COLOR_OFF, func_name + 5, line);
        failed_tests++;
    }
}

#define ASSERT_TEST(expr) (assert_test(expr ? 0 : 1, __func__, __LINE__))
#define NUM_OF_ERRORS failed_tests

static int SHOW_PRINT = 0;
#define PRINT_TEST if (SHOW_PRINT) printf("Executing Test" BOLD_ON " %s()" BOLD_OFF "...\n", __func__ + 5)

#endif
