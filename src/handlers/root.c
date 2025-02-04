#include "../../include/request.h"
#include <stdlib.h>
#include <string.h>

void get_root(struct Request *request, struct Response *response) {
  response->status = OK;
  response->status_text = status_text(response->status);
  response->body = "<h1>Hello, world!</h1>";

  unsigned long body_length = strlen(response->body);

  response->header_count = 2;
  response->headers =
      (struct Header *)malloc(sizeof(struct Header) * response->header_count);

  response->headers[0] = CONTENT_TYPE(MIME_TEXT_HTML);
  response->headers[1] = CONTENT_LENGTH(itoa(body_length));
}
