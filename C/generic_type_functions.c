#include "generic_type_functions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Type
{
    Free free_value;
    Copy copy_value;
    Compare compare_value;
}Type;

Type type_init(Free free_value, Copy copy_value, Compare compare_value)
{
  Type result;
  result.free_value = free_value;
  result.copy_value = copy_value;
  result.compare_value = compare_value;

  return result;
}
