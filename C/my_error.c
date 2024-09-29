#include <stdio.h>
#include "my_error.h"

static enum MY_ERROR last_error = 0;

void my_error_set(enum MY_ERROR error)
{
    last_error = error;        
}

const int my_error_get()
{
    return last_error;
}

int my_error_failed()
{
    return last_error > 0;
}

void my_error_throw()
{
    if(my_error_failed())
        printf(BOLD_ON RED_ON "%s\n" COLOR_OFF BOLD_OFF, last_error);

