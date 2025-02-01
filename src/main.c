#include "../include/argparse.h"
#include "../include/socket.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int port = get_port(argc, argv);
  printf("Running on port %d\n", port);

  int socket = create_socket();
  set_socket_options(socket);
  bind_socket(socket, port);
  listen_socket(socket);

  int counter = 0;
  int client;
  while (1) {
    client = accept_socket(socket);

    close_socket(client);
  }
  return 0;
}
