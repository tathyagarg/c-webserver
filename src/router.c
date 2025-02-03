#include "../include/request.h"
#include "../include/routing.h"
#include <string.h>

void not_found(struct Request *request, struct Response *response) {
  response->status = NOT_FOUND;
  response->status_text = status_text(NOT_FOUND);
  response->header_count = 0;
  response->body = "404 Not Found";
}

void process_request(struct Request *request, struct Response *response,
                     struct Router *router) {
  for (int i = 0; i < router->count; i++) {
    if (strcmp(request->target, router->paths[i]) == 0) {
      router->handlers[i](request, response);
      return;
    }
  }
  not_found(request, response);
}
