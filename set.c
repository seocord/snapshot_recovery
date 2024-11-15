#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set(kvs_t* kvs, const char* key, const char* value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (!new_node) {
    fprintf(stderr, "Failed to allocate memory for node\n");
    return -1;
  }

  strcpy(new_node->key, key);
  new_node->value = strdup(value);
  new_node->next = kvs->db;
  kvs->db = new_node;
  kvs->items++;

  return 0;
}
