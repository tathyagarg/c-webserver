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

struct Request *parse_request(char *buffer, struct Request *request) {
  request->method = parse_method(strtok_r(buffer, " ", &buffer));
  request->target = strtok_r(buffer, " ", &buffer);
  request->protocol = parse_protocol(strtok_r(buffer, "\r\n", &buffer));
  request->headers = malloc(sizeof(struct Header) * DEFAULT_MAX_HEADER_COUNT);

  // Headers
  char *line = strtok_r(buffer, "\r\n", &buffer);
  int i = 0;
  while (line != NULL) {
    if (i >= DEFAULT_MAX_HEADER_COUNT) {
      request->headers =
          realloc(request->headers, sizeof(struct Header) * i * 2);
    }

    char *key = strtok(line, ": ");
    char *value = strtok(NULL, "\r\n");

    // Skip leading space
    value += sizeof(char);

    request->headers[i].key = key;
    request->headers[i].value = value;
    i++;

    line = strtok_r(buffer, "\r\n", &buffer);
  }
  request->header_count = i;

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

enum HTTP_Protocol parse_protocol(char *protocol) {
  if (strcmp(protocol, "HTTP/1.0") == 0) {
    return HTTP_1_0;
  } else if (strcmp(protocol, "HTTP/1.1") == 0) {
    return HTTP_1_1;
  }
  return UNKNOWN_PROTOCOL;
}

char *make_response(struct Response *response) {
  char *response_text = malloc(1024);
  sprintf(response_text, "HTTP/1.1 %d %s", response->status,
          status_text(response->status));

  for (int i = 0; i < response->header_count; i++) {
    sprintf(response_text + strlen(response_text), "\r\n%s: %s",
            response->headers[i].key, response->headers[i].value);
  }
  sprintf(response_text + strlen(response_text), "\r\n\r\n%s", response->body);

  return response_text;
}

char *itoa(unsigned long val) {
  static char buf[32] = {0};
  int i = 30;
  for (; val && i; --i, val /= 10) {
    buf[i] = "0123456789"[val % 10];
  }
  return &buf[i + 1];
}
