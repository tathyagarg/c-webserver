#include "../include/socket.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BACKLOG 10

int create_socket() { return socket(AF_INET, SOCK_STREAM, 0); }

int close_socket(int socket) {
  shutdown(socket, SHUT_RDWR);
  return close(socket);
}

int set_socket_options(int socket) {
  return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
}

int bind_socket(int socket, int port) {
  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_port = htons(port),
      .sin_addr = {.s_addr = INADDR_ANY},
  };
  return bind(socket, (struct sockaddr *)&addr, sizeof(addr));
}

int listen_socket(int socket) { return listen(socket, MAX_BACKLOG); }

int accept_socket(int socket) {
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  return accept(socket, (struct sockaddr *)&addr, &addr_len);
}
