#ifndef hash_map_h
#define hash_map_h

#include "generic_type_functions.h"
#include "vector.h"

typedef int (*Hash)(void*);

typedef struct Pair
{
    void* key;
    void* value;
    Type key_type;
    Type value_type;
}Pair;

typedef struct HashMap
{
    Vector** buckets;
    Hash hash;
    int size;
    int number_of_elements;
    int prime_index;
    Type key_type;
    Type value_type;
}HashMap;

HashMap* hash_map_init(Type key_type, Type value_type, Hash hash); 

void hash_map_put(HashMap* hash_map, void* key, void* value);

void hash_map_free(HashMap* hash_map);

#endif

