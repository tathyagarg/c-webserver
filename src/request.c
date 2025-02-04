#include "../include/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *status_text(enum Status status) {
  switch (status) {
  case OK:
    return "OK";
  case CREATED:
    return "Created";
  case ACCEPTED:
    return "Accepted";
  case NON_AUTHORITATIVE_INFORMATION:
    return "Non-Authoritative Information";
  case NO_CONTENT:
    return "No Content";
  case RESET_CONTENT:
    return "Reset Content";
  case MOVED_PERMANENTLY:
    return "Moved Permanently";
  case FOUND:
    return "Found";
  case SEE_OTHER:
    return "See Other";
  case NOT_MODIFIED:
    return "Not Modified";
  case TEMPORARY_REDIRECT:
    return "Temporary Redirect";
  case PERMANENT_REDIRECT:
    return "Permanent Redirect";
  case BAD_REQUEST:
    return "Bad Request";
  case UNAUTHORIZED:
    return "Unauthorized";
  case PAYMENT_REQUIRED:
    return "Payment Required";
  case FORBIDDEN:
    return "Forbidden";
  case NOT_FOUND:
    return "Not Found";
  case METHOD_NOT_ALLOWED:
    return "Method Not Allowed";
  case NOT_ACCEPTABLE:
    return "Not Acceptable";
  case REQUEST_TIMEOUT:
    return "Request Timeout";
  case CONFLICT:
    return "Conflict";
  case GONE:
    return "Gone";
  case LENGTH_REQUIRED:
    return "Length Required";
  case CONTENT_TOO_LARGE:
    return "Content Too Large";
  case URI_TOO_LONG:
    return "URI Too Long";
  case UNSUPPORTED_MEDIA_TYPE:
    return "Unsupported Media Type";
  case EXPECTATION_FAILED:
    return "Expectation Failed";
  case IM_A_TEAPOT:
    return "I'm a teapot";
  case UPGRADE_REQUIRED:
    return "Upgrade Required";
  case TOO_MANY_REQUESTS:
    return "Too Many Requests";
  case INTERNAL_SERVER_ERROR:
    return "Internal Server Error";
  case NOT_IMPLEMENTED:
    return "Not Implemented";
  case BAD_GATEWAY:
    return "Bad Gateway";
  case SERVICE_UNAVAILABLE:
    return "Service Unavailable";
  case GATEWAY_TIMEOUT:
    return "Gateway Timeout";
  case HTTP_VERSION_NOT_SUPPORTED:
    return "HTTP Version Not Supported";
  }
  return "Unknown Status";
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
  } else if (strcmp(method, "HEAD") == 0) {
    return HEAD;
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

char *read_from(char *fname) {
  // Read from fname and return the contents
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(fsize + 1);
  fread(string, 1, fsize, f);
  fclose(f);

  string[fsize] = 0;
  return string;
}

void file_response(char *fname, struct Response *response, char *mime_type) {
  response->status = OK;
  response->status_text = status_text(OK);
  response->body = read_from(fname);
  response->header_count = 2;
  response->headers =
      (struct Header *)malloc(sizeof(struct Header) * response->header_count);

  unsigned long len = strlen(response->body);
  char *len_str = itoa(len);

  response->headers[0] = CONTENT_TYPE(mime_type);
  response->headers[1] = CONTENT_LENGTH(len_str);
}
