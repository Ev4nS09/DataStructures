#ifndef generic_type_functions_h
#define generic_type_functions_h

typedef void (*Free)(void*);
typedef void* (*Copy)(void*);
typedef int (*Compare)(void*, void*);
typedef void (*Print)(void*);

#define COPY(copy_value, value) (value ? (copy_value ? copy_value(value) : value) : NULL)

#endif // !

