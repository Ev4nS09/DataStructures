#ifndef my_error_h 
#define my_error_h 

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define RED_ON "\033[31m"
#define COLOR_OFF "\033[m"

enum MY_ERROR
{
    SUCCESS,
    OUT_OF_BOUNDS,
    INVALID_VALUE,
};

void my_error_set(enum MY_ERROR error);

const int my_error_get();

int my_error_failed();

#endif
