#ifndef SOCKET_H
#define SOCKET_H

int create_socket();
int close_socket(int socket);
int set_socket_options(int socket);
int bind_socket(int socket, int port);
int listen_socket(int socket);
int accept_socket(int socket);

#endif
