#ifndef REQUEST_H
#define REQUEST_H

#define DEFAULT_MAX_HEADER_COUNT 10
#define DEFAULT_MAX_QUERY_COUNT 10

enum Method {
  GET,
  POST,
  PUT,
  DELETE,
  HEAD,
  UNKNOWN,
};

enum HTTP_Protocol {
  HTTP_1_0,
  HTTP_1_1,
  UNKNOWN_PROTOCOL,
};

enum Status {
  OK = 200,
  CREATED = 201,
  ACCEPTED = 202,
  NON_AUTHORITATIVE_INFORMATION = 203,
  NO_CONTENT = 204,
  RESET_CONTENT = 205,
  MOVED_PERMANENTLY = 301,
  FOUND = 302,
  SEE_OTHER = 303,
  NOT_MODIFIED = 304,
  TEMPORARY_REDIRECT = 307,
  PERMANENT_REDIRECT = 308,
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  PAYMENT_REQUIRED = 402,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,
  NOT_ACCEPTABLE = 406,
  REQUEST_TIMEOUT = 408,
  CONFLICT = 409,
  GONE = 410,
  LENGTH_REQUIRED = 411,
  CONTENT_TOO_LARGE = 413,
  URI_TOO_LONG = 414,
  UNSUPPORTED_MEDIA_TYPE = 415,
  EXPECTATION_FAILED = 417,
  IM_A_TEAPOT = 418,
  UPGRADE_REQUIRED = 426,
  TOO_MANY_REQUESTS = 429,
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
  BAD_GATEWAY = 502,
  SERVICE_UNAVAILABLE = 503,
  GATEWAY_TIMEOUT = 504,
  HTTP_VERSION_NOT_SUPPORTED = 505,
};

struct Header {
  char *key;
  char *value;
};

struct Query {
  char *key;
  char *value;
};

struct Request {
  enum Method method;
  char *target;
  enum HTTP_Protocol protocol;
  struct Header *headers;
  int header_count;
  struct Query *query;
  int query_count;
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

char *read_from(char *fname);
void file_response(char *fname, struct Response *response, char *mime_type);

#define MIME_TEXT_PLAIN "text/plain"
#define MIME_TEXT_HTML "text/html"
#define MIME_TEXT_CSS "text/css"
#define MIME_TEXT_JS "text/javascript"

#define CONTENT_TYPE(x)                                                        \
  (struct Header) { .key = "Content-Type", .value = x }

#define CONTENT_LENGTH(x)                                                      \
  (struct Header) { .key = "Content-Length", .value = x }

#endif
