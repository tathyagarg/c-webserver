#include "../../include/request.h"
#include <stdlib.h>
#include <string.h>

void get_root(struct Request *request, struct Response *response) {
  response->status = OK;
  response->status_text = status_text(OK);
  response->body = request->target;

  response->header_count = 2;
  response->headers =
      (struct Header *)malloc(sizeof(struct Header) * response->header_count);

  unsigned long len = strlen(response->body);
  char *len_str = itoa(len);

  response->headers[0] = CONTENT_TYPE(MIME_TEXT_PLAIN);
  response->headers[1] = CONTENT_LENGTH(len_str);
}

void get_get_ep(struct Request *request, struct Response *response) {
  response->status = OK;
  response->status_text = status_text(OK);
  response->body = read_from("templates/index.html");
  response->header_count = 2;
  response->headers =
      (struct Header *)malloc(sizeof(struct Header) * response->header_count);

  unsigned long len = strlen(response->body);
  char *len_str = itoa(len);

  response->headers[0] = CONTENT_TYPE(MIME_TEXT_HTML);
  response->headers[1] = CONTENT_LENGTH(len_str);
}
