#include "kvs.h"

kvs_t* openKVS() {
  kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));
  if (kvs) {
    kvs->items = 0;
    kvs->db = NULL;
    return kvs;
  }
  return NULL;
}
