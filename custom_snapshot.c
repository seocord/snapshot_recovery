#include "kvs.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void do_custom_snapshot(kvs_t* kvs) {
  int fd, returnval;

  fd = open("kvs.img", O_RDWR | O_CREAT, 0644);
  if (fd < 0) {
    perror("open");
    return;
  }

  node_t* current = kvs->db;
  for (int i = 0; i < kvs->items; i++) {
    write(fd, current->key, strlen(current->key));
    write(fd, "\n", 1);
    write(fd, current->value, strlen(current->value));
    write(fd, "\n", 1);
    current = current->next;
  }

  close(fd);
}
