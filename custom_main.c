#include <stdio.h>
#include <time.h>
#include <sys/resource.h>  // 헤더 추가
#include "kvs.h"

void print_memory_usage(const char* label) {
  struct rusage r_usage;
  getrusage(RUSAGE_SELF, &r_usage);
  printf("[%s] Memory usage: %ld KB\n", label, r_usage.ru_maxrss);
}

int main() {
  print_memory_usage("Before workload");

  kvs_t* kvs = openKVS();

  clock_t start_recovery = clock();
  kvs = do_custom_recovery(kvs);
  clock_t end_recovery = clock();
  printf("do_custom_recovery 실행 시간: %f 초\n", ((double)(end_recovery - start_recovery)) / CLOCKS_PER_SEC);

  if (!kvs) {
    printf("Failed to open kvs\n");
    return -1;
  }

  FILE* fp1 = fopen("cluster004.trc", "r");
  FILE* fp2 = fopen("answer.dat", "w");

  char line[30];
  while (fgets(line, sizeof(line), fp1) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    char* command = strtok(line, ",");
    char* key = strtok(NULL, ",");
    char* value = strtok(NULL, ",");

    if (command != NULL && key != NULL) {
      if (strcmp(command, "get") == 0) {
        char* result = get(kvs, key);
        if (result != NULL) {
          fprintf(fp2, "%s\n", result);
        } else {
          fprintf(fp2, "%d\n", -1);
        }
      } else if (strcmp(command, "set") == 0 && value != NULL) {
        set(kvs, key, value);
      }
    }
  }

  clock_t start_snapshot = clock();
  do_custom_snapshot(kvs);
  clock_t end_snapshot = clock();
  printf("do_custom_snapshot 실행 시간: %f 초\n", ((double)(end_snapshot - start_snapshot)) / CLOCKS_PER_SEC);

  print_memory_usage("After custom snapshot");

  fclose(fp1);
  fclose(fp2);
  closeKVS(kvs);
  return 0;
}
