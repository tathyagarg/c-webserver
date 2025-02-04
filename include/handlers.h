#ifndef HANDLERS_H
#define HANDLERS_H

#include "request.h"

void get_root(struct Request *request, struct Response *response);
void get_get_ep(struct Request *request, struct Response *response);

#endif
