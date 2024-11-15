#include "kvs.h"

void do_baseline_snapshot(kvs_t* kvs) {
  FILE* fp = fopen("kvs.img", "w");
  node_t* current = kvs->db;
  for (int i = 0; i < kvs->items; i++) {
    char* key = current->key;
    char* value = current->value;
    fprintf(fp, "%s\n%s\n", key, value);
    current = current->next;
  }
  fclose(fp);
}
