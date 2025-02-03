#ifndef ROUTING_H
#define ROUTING_H

#include "request.h"

struct Router {
  char **paths;
  void (**handlers)(struct Request *, struct Response *);
  enum Method *methods;
  int count;
};

void process_request(struct Request *request, struct Response *response,
                     struct Router *router);
void add_route(struct Router *router, char *path,
               void (*handler)(struct Request *, struct Response *),
               enum Method method);

#endif
