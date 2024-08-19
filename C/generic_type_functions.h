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

#endif // !

