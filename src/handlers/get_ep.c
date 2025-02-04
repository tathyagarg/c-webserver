#include "../../include/request.h"
#include <stdio.h>

void get_get_ep(struct Request *request, struct Response *response) {
  file_response("templates/get_ep.html", response, MIME_TEXT_HTML);
}
