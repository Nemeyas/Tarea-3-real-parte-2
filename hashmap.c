#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  int i=hash(key, map -> capacity);

  while(map -> buckets[i] != NULL && strcmp(map->buckets[i] -> key, key) != 0){
    i = ((i+1)%map->capacity);
  }
  if(map->buckets[i]==NULL){
    Pair *valor= createPair(key,value);
    map->buckets[i]=valor;
    map->size++;
  }
  else{
    map->buckets[i]->key=key;
    map->buckets[i]->value=value;
  }
  map->current=i;
}

void enlarge(HashMap * map) {
  int auxcap = map->capacity;
  Pair **old_buckets = map->buckets;
  map->capacity *= 2;
  map->size=0;
  map->buckets=(Pair **)calloc(map->capacity,sizeof(Pair*));

  for(int i = 0 ; i < auxcap ; i++){
    if(old_buckets[i] != NULL){
      insertMap(map,old_buckets[i]->key,old_buckets[i]->value);
    }
  }

  enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
    HashMap *mapa=(HashMap*)malloc(sizeof(HashMap));
    
    mapa->current=-1;
    mapa->buckets=(Pair **)calloc(capacity,sizeof(Pair *));;
    mapa->capacity=capacity;
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  int i=hash(key, map->capacity);
  int first=i;
  while(map->buckets[i] != NULL){
    if(is_equal(map->buckets[i]->key, key)==1){
      map->size--;
      map->buckets[i]->key=NULL;
      break;
    }
    i=((i+1)%map->capacity);
    if(first==i) break;
  }

}

Pair * searchMap(HashMap * map,  char * key) {   
  int i = hash( key, map->capacity);
  int aux=i;
  
  while(map -> buckets[i] != NULL && strcmp(map->buckets[i]->key, key) != 0){
    i = ((i + 1) % map -> capacity);
    if(i==aux) {
      return NULL;
    }
    }
  map->current= i;
  return map-> buckets[i];
}

Pair * firstMap(HashMap * map) {
  if(map->size==0){
    return NULL;
  }
  int i=0;
  while (map->buckets[i]==NULL || map->buckets[i]->key==NULL){
    i++;
    if (i >= map->capacity) return NULL;
  }
  /*for(i=0; i<map->capacity; i++){
    if(map->buckets[i] != NULL){
      map->current = i;
      if (i >= map->capacity){
        return NULL;
      } 
    }
  } Por que no sirve este ciclo?*/
  map->current = i;
  return map->buckets[i];
}

Pair * nextMap(HashMap * map) {
if(map->current==-1){
    return NULL; 
  }
  for(long i = map->current+1; i < map->capacity; i++){
    if (*(map->buckets+i) != NULL && (*(map->buckets+i))->key != NULL) { 
    map->current = i;
    return *(map->buckets+i);
    }
  }
  map->current=-1;
  return NULL;
}