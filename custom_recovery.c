#include "kvs.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

kvs_t* do_custom_recovery(kvs_t* kvs) {
  int fd, nbytes;
  char buffer[5000];
  node_t* new_node = NULL;

  fd = open("kvs.img", O_RDONLY);
  if (fd < 0) {
    perror("open");
    return kvs;
  }

  while ((nbytes = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[nbytes] = '\0';

    // Parsing logic and insertion (similar to baseline)

  }

  close(fd);
  return kvs;
}
