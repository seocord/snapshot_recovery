#include "kvs.h"
#include <stdlib.h>

int closeKVS(kvs_t* kvs) {
  if (kvs != NULL) {
    node_t* current = kvs->db;
    while (current != NULL) {
      node_t* next = current->next;
      free(current->value);
      free(current);
      current = next;
    }
    free(kvs);
  }
  return 0;
}
