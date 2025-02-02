#include "../include/argparse.h"
#include "../include/request.h"
#include "../include/socket.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFLEN 1024

int main(int argc, char *argv[]) {
  int port = get_port(argc, argv);
  printf("Running on port %d\n", port);

  int socket = create_socket();
  set_socket_options(socket);
  bind_socket(socket, port);
  listen_socket(socket);

  int client;

  char *buffer = malloc(MAX_BUFLEN);
  char *response = "HTTP/1.1 200 OK\nContent-Length: 12\n\nHello World!";
  int response_len = strlen(response);

  while (1) {
    client = accept_socket(socket);
    read_socket(client, buffer, MAX_BUFLEN);
    struct Request *request = parse_request(buffer);
    printf("Path: %s\n", request->path);
    printf("Method: %d\n", request->method);

    write_socket(client, response, response_len);

    close_socket(client);
  }
  return 0;
}
