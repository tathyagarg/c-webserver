#include "../include/argparse.h"
#include "../include/handlers.h"
#include "../include/request.h"
#include "../include/routing.h"
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

  struct Router *router = malloc(sizeof(struct Router));
  router->count = 1;
  router->paths = malloc(sizeof(char *));
  router->handlers =
      malloc(sizeof(void (*)(struct Request *, struct Response *)));
  router->methods = malloc(sizeof(enum Method));

  router->paths[0] = "/";
  router->handlers[0] = get_root;
  router->methods[0] = GET;

  while (1) {
    client = accept_socket(socket);
    read_socket(client, buffer, MAX_BUFLEN);
    struct Request *request = malloc(sizeof(struct Request));
    parse_request(buffer, request);

    struct Response *response = malloc(sizeof(struct Response));
    process_request(request, response, router);

    char *response_text = make_response(response);

    write_socket(client, response_text, strlen(response_text));

    close_socket(client);
    free(request);
    if (response->header_count > 0) {
      free(response->headers);
    }
    free(response);
    free(response_text);
  }
  free(router->handlers);
  free(router->paths);
  free(router->methods);
  free(router);

  return 0;
}
