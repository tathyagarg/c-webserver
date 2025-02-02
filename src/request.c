#include "../include/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *status_text(enum Status status) {
  switch (status) {
  case OK:
    return "OK";
  case BAD_REQUEST:
    return "Bad Request";
  case NOT_FOUND:
    return "Not Found";
  case METHOD_NOT_ALLOWED:
    return "Method Not Allowed";
  case INTERNAL_SERVER_ERROR:
    return "Internal Server Error";
  default:
    return "Unknown";
  }
}

struct Request *parse_request(char *buffer) {
  struct Request *request = malloc(sizeof(struct Request));
  request->method = parse_method(strtok(buffer, " "));
  request->path = strtok(NULL, " ");

  return request;
}

enum Method parse_method(char *method) {
  if (strcmp(method, "GET") == 0) {
    return GET;
  } else if (strcmp(method, "POST") == 0) {
    return POST;
  } else if (strcmp(method, "PUT") == 0) {
    return PUT;
  } else if (strcmp(method, "DELETE") == 0) {
    return DELETE;
  }
  return UNKNOWN;
}
