#include "../include/request.h"
#include "../include/routing.h"
#include <string.h>

void process_request(struct Request *request, struct Response *response,
                     struct Router *router) {
  for (int i = 0; i < router->count; i++) {
    if (strcmp(request->target, router->paths[i]) == 0) {
      router->handlers[i](request, response);
      return;
    }
  }
}
