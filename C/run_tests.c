#include <stdio.h>
#include <stdlib.h>
#include "vector_tests.h"
#include "vector.h"
#include "tests_util.h"

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"
#define GREEN_ON "\033[32m"
#define COLOR_OFF "\033[m"

int main(int argc, char* argv[])
{
    Vector* v = vector_init(32);


    vector_add(int, v, 10);
    int x = _vector_get(int, v, 0);

    vector_destroy(v, NULL);

    test_vector(((int) argv[1][0]) - '0');

    if(NUM_OF_ERRORS == 0)
        printf(GREEN_ON " All Tests Passed.\n" COLOR_OFF);
    else
        printf(RED_ON "%d Tests failed.\n" COLOR_OFF, failed_tests);
    
    return 0;
}

