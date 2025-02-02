#ifndef REQUEST_H
#define REQUEST_H

#define DEFAULT_MAX_HEADER_COUNT 10

enum Method {
  GET,
  POST,
  PUT,
  DELETE,
  UNKNOWN,
};

enum HTTP_Protocol {
  HTTP_1_0,
  HTTP_1_1,
  UNKNOWN_PROTOCOL,
};

enum Status {
  OK = 200,
  BAD_REQUEST = 400,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,
  INTERNAL_SERVER_ERROR = 500,
};

struct Header {
  char *key;
  char *value;
};

struct Request {
  enum Method method;
  char *target;
  enum HTTP_Protocol protocol;
  struct Header *headers;
  int header_count;
  char *body;
};

struct Response {
  enum HTTP_Protocol protocol;
  enum Status status;
  char *status_text;
  struct Header *headers;
  int header_count;
  char *body;
};

char *status_text(enum Status status);
struct Request *parse_request(char *buffer, struct Request *request);
enum Method parse_method(char *method);
enum HTTP_Protocol parse_protocol(char *protocol);
char *make_response(struct Response *response);
char *itoa(unsigned long val);

#endif
