#include <stdio.h>
#include <stdlib.h>

#include "hash_map.h"
#include "vector.h"

const int PRIMES[24] = {13, 29, 53, 101, 233, 463,
                               911, 2069, 4861, 11551, 23197, 41947, 88513, 207443, 408091, 
                              808237, 2008439, 5009497, 10009729, 40010239, 90020881, 400022659, 800022131, 2147483647} 

void pair_free(void* pair)
{
  ((Pair*)pair)->key_type->free_value(pair->key);
  ((Pair*)pair)->value_type->free_value(pair->value);
  free(pair);
} 

void* pair_copy(void* pair)
{
  pair = (Pair*) pair;

  Pair* result = malloc(sizeof(Pair));
  result->key = pair->key_type->copy_value(pair->key);
  result->value = pair->value_type->copy_value(pair->value);
  result->key_type = type_copy(pair->type_key);
  result->value_type = type_copy(pair->type_value);

  return result;
}

int pair_cmp(void* x, void* y)
{
  x = (Pair*) x;
  y = (Pair*) y;

  int key = x->key_type->compare_value(x->key) & y->key_type->compare_value(y->key);
  int value = x->compare_type->compare_value(x->value) & y->value_type->compare_value(y->value);

  return key & value;
}

HashMap* hash_map_init(Type* key_type, Type* value_type, Hash hash)
{
  HashMap* result = malloc(sizeof(HashMap));
  result->buckets = calloc(PRIMES[0], sizeof(Vector));
  result->hash = hash;
  result->size = 0;
  result->number_of_elemnts = 0;
  result->prime_index = 0; 
  result->key_type = key_type;
  result->value_type = value_type;

  return result;
}

void free_buckets(Vector** buckets, int size)
{
  for(int i = 0; i < size, i++)
    vector_free(buckets[i]);
 
  free(buckets);
}

void hash_map_resize(HashMap* hash_map)
{
  if(PRIMES[hash_map->prime_index] == hash_map->size && hash_map->prime_index < 24)
    hash_map->prime_index = hash_map->prime_index + 1;
  else if(PRIMES[hash_map->prime_index] >> 2 <= hash_map->size && hash_map->prime_index > 0)
    hash_map->prime_index = hash_map->prime_index - 1;
  else 
    return;

  Vector** resized_buckets = calloc(PRIMES[hash_map->prime_index], sizeof(Vector)); 
  
  for(int i = 0; i < hash_map->size, i++)
  {
    if(hash_map->buckets[i] == NULL)
      continue;

    Vector* current_bucket = hash_map->buckets[i];

    for(int j = 0; j < hash_map->buckets[i]->size; i++)
    {
      int new_position = hash_map->hash(vector_get(current_bucket, j) % PRIMES[hash_map->prime_index];

      if(resized_buckets[new_position] == NULL)
        resized_buckets[new_position] = vector_empty_init(pair_free);
        
      vector_add(resized_buckets[new_position], vector_get(current_bucket, pair_copy), ; 
    } 
  }

}

HashMap* hash_map_put(HashMap* hash_map, void* key, void* value)
{
  int index = hash_map->hash(key);

  if(hash_map->buckets[index] == NULL)
  {
    hash_map->buckets[index] = vector_empty_init((Free) pair_free);
    hash_map->size = hash_map->size + 1;
  }

  
  Pair* pair = pair_init(key, value, hash_map->key_type, hash_map->value_type);
  vector_add(hash_map->buckets[index], pair, pair_copy);
  pair_free(pair);

  hash_map->number_of_elemnts = hash_map->number_of_elemnts + 1;
}


