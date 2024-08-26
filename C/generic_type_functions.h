#ifndef generic_type_functions_h
#define generic_type_functions_h

typedef void (*Free)(void*);
typedef void* (*Copy)(void*);
typedef int (*Compare)(void*, void*);
typedef void (*Print)(void*);

typedef struct Type
{
    Free free_value;
    Copy copy_value;
    Compare compare_value;
}Type;

static Type type_init(Free free_value, Copy copy_value, Compare compare_value)
{
  Type result;
  result.free_value = free_value;
  result.copy_value = copy_value;
  result.compare_value = compare_value;

  return result;
}

/*static Type* type_copy(Type* type)
{
  return type_init(type->free_value, type->copy_value, type->compare_value);
}*/

#endif // !

