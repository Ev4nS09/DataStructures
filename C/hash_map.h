#ifndef hash_map_h
#define hash_map_h

#include "generic_type_functions.h"
#include "vector.h"

typedef int (*Hash)(void*);

typedef struct Pair
{
    void* key;
    void* value;
}Pair;

typedef struct HashMap
{
    Vector* buckets;
    Hash hash;
    int size;
}HashMap;


#endif

