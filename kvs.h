#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  char key[100];
  char* value;
  struct node* next;
};
typedef struct node node_t;

struct kvs {
  struct node* db;  // database
  int items;        // number of data
};
typedef struct kvs kvs_t;

kvs_t* openKVS();
int closeKVS(kvs_t* kvs);
int set(kvs_t* kvs, const char* key, const char* value);
char* get(kvs_t* kvs, const char* key);
kvs_t* do_baseline_recovery(kvs_t* kvs);
void do_baseline_snapshot(kvs_t* kvs);
kvs_t* do_custom_recovery(kvs_t* kvs);
void do_custom_snapshot(kvs_t* kvs);
