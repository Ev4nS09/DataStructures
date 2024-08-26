#include <stdio.h>
#include <stdlib.h>

#include "hash_map.h"
#include "vector.h"
#include "generic_type_functions.h"

const int PRIMES[24] = {13, 29, 53, 101, 233, 463,
                               911, 2069, 4861, 11551, 23197, 41947, 88513, 207443, 408091, 
                              808237, 2008439, 5009497, 10009729, 40010239, 90020881, 400022659, 800022131, 2147483647}; 

void pair_free(void* pair)
{
  ((Pair*)pair)->key_type.free_value(((Pair*)pair)->key);
  ((Pair*)pair)->value_type.free_value(((Pair*)pair)->value);
  free(pair);
} 

void* pair_copy(void* void_pair)
{
  Pair* pair = (Pair*) void_pair;

  Pair* result = malloc(sizeof(Pair));
  result->key = pair->key_type.copy_value(pair->key);
  result->value = pair->value_type.copy_value(pair->value);
  result->key_type = pair->key_type;
  result->value_type = pair->value_type;

  return result;
}

int pair_cmp(void* pair1, void* pair2)
{
  Pair* x = (Pair*) pair1;
  Pair* y = (Pair*) pair2;

  int key = x->key_type.compare_value(x->key, y->key);
  int value = x->value_type.compare_value(x->value, y->value); 

  return key & value;
}

Pair* pair_init(void* key, void* value, Type key_type, Type value_type)
{
  Pair* pair = malloc(sizeof(Pair));
  pair->key = key;
  pair->value = value;
  pair->key_type = key_type;
  pair->value_type = value_type;

  return pair;
}

HashMap* hash_map_init(Type key_type, Type value_type, Hash hash)
{
  HashMap* result = malloc(sizeof(HashMap));
  result->buckets = calloc(PRIMES[0], sizeof(Vector));
  result->hash = hash;
  result->size = 0;
  result->number_of_elements = 0;
  result->prime_index = 0; 
  result->key_type = key_type;
  result->value_type = value_type;

  return result;
}

void free_buckets(Vector** buckets, int size)
{
  for(int i = 0; i < size; i++)
  {
    if(buckets[i] != NULL)
    {
      vector_free(buckets[i]);
    }
  }
 
  free(buckets);
}

void hash_map_resize(HashMap* hash_map)
{
  Vector** resized_buckets = calloc(PRIMES[hash_map->prime_index], sizeof(Vector)); 
  
  for(int i = 0; i < hash_map->size; i++)
  {
    if(hash_map->buckets[i] == NULL)
      continue;

    Vector* current_bucket = hash_map->buckets[i];

    for(int j = 0; j < hash_map->buckets[i]->size; i++)
    {
      Pair* pair = (Pair*) vector_get(current_bucket, j, pair_copy);
      int new_position = hash_map->hash(pair->key) % PRIMES[hash_map->prime_index];
      pair_free(pair);

      if(resized_buckets[new_position] == NULL)
        resized_buckets[new_position] = vector_empty_init(pair_free);
        
      vector_add_no_copy(resized_buckets[new_position], vector_get(current_bucket, j, pair_copy)) ; 
    } 
  }

  free_buckets(hash_map->buckets, hash_map->size);
  hash_map->buckets = resized_buckets;
}

void hash_map_put(HashMap* hash_map, void* key, void* value)
{
  int index = hash_map->hash(key) % PRIMES[hash_map->prime_index];

  if(hash_map->buckets[index] == NULL)
  {
    hash_map->buckets[index] = vector_empty_init(pair_free);
    hash_map->size = hash_map->size + 1;
  }

  vector_add_no_copy(hash_map->buckets[index], pair_init(hash_map->key_type.copy_value(key), hash_map->value_type.copy_value(value), hash_map->key_type, hash_map->value_type));

  if(hash_map->size == PRIMES[hash_map->prime_index] && hash_map->prime_index < 24)
  {
    hash_map->prime_index = hash_map->prime_index + 1;
    hash_map_resize(hash_map);
  }

  hash_map->number_of_elements = hash_map->number_of_elements + 1;
}

void hash_map_free(HashMap* hash_map)
{
  free_buckets(hash_map->buckets, PRIMES[hash_map->prime_index]);
  free(hash_map);
}

