#include "../include/argparse.h"
#include <stdlib.h>
#include <string.h>

int get_port(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--port") == 0) {
      return atoi(argv[i + 1]);
    }
  }
  return 0;
}
