#include "../include/request.h"
#include "../include/routing.h"
#include <stdlib.h>
#include <string.h>

void add_route(struct Router *router, char *path,
               void (*handler)(struct Request *, struct Response *),
               enum Method method) {
  router->count++;
  router->paths = realloc(router->paths, sizeof(char *) * router->count);
  router->handlers = realloc(
      router->handlers,
      sizeof(void (*)(struct Request *, struct Response *)) * router->count);
  router->methods =
      realloc(router->methods, sizeof(enum Method) * router->count);

  router->paths[router->count - 1] = path;
  router->handlers[router->count - 1] = handler;
  router->methods[router->count - 1] = method;
}

void not_found(struct Request *request, struct Response *response) {
  response->status = NOT_FOUND;
  response->status_text = status_text(NOT_FOUND);
  response->header_count = 0;
  response->body = "404 Not Found";
}

void process_request(struct Request *request, struct Response *response,
                     struct Router *router) {
  if (request->protocol == UNKNOWN_PROTOCOL) {
    response->status = HTTP_VERSION_NOT_SUPPORTED;
    response->status_text = status_text(HTTP_VERSION_NOT_SUPPORTED);
    response->header_count = 0;
    response->body = "505 HTTP Version Not Supported";
    return;
  }

  for (int i = 0; i < router->count; i++) {
    if (strcmp(request->target, router->paths[i]) == 0) {
      if (request->method != router->methods[i]) {
        response->status = METHOD_NOT_ALLOWED;
        response->status_text = status_text(METHOD_NOT_ALLOWED);
        response->header_count = 0;
        response->body = "405 Method Not Allowed";
        return;
      }
      router->handlers[i](request, response);
      return;
    }
  }
  not_found(request, response);
}
