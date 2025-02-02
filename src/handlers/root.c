#include "../../include/request.h"
#include <stdlib.h>
#include <string.h>

void get_root(struct Request *request, struct Response *response) {
  response->status = OK;
  response->status_text = status_text(OK);
  response->body = request->target;
  response->body[1] = 0;
  response->headers = (struct Header *)malloc(sizeof(struct Header *) * 10);

  unsigned long len = strlen(response->body);
  char *len_str = itoa(len);

  response->headers[0] = (struct Header){"Content-Type", "text/plain"};
  response->headers[1] = (struct Header){"Content-Length", len_str};
  response->header_count = 2;
}
