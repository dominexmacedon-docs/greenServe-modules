#include "evaluator.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define GS_SERVER_BUFFER 32768
#define GS_SERVER_MAX_BODY (16 * 1024 * 1024)
#define GS_SERVER_MAX_HEADER 65536
#define GS_SERVER_BACKLOG 64
#define GS_SERVER_VERSION "greenServe-libserver/1.1"

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} Buffer;

static char *gs_dup(const char *s) {
    size_t n = strlen(s ? s : "");
    char *p = malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, s ? s : "", n + 1);
    return p;
}

static void buffer_free(Buffer *b) {
    if (!b) return;
    free(b->data);
    b->data = NULL;
    b->len = b->cap = 0;
}

static int buffer_reserve(Buffer *b, size_t extra) {
    if (extra > GS_SERVER_MAX_BODY || b->len > GS_SERVER_MAX_BODY - extra) return 0;
    size_t need = b->len + extra + 1;
    if (need <= b->cap) return 1;
    size_t cap = b->cap ? b->cap : 4096;
    while (cap < need) {
        if (cap > GS_SERVER_MAX_BODY / 2) {
            cap = GS_SERVER_MAX_BODY;
            break;
        }
        cap *= 2;
    }
    char *p = realloc(b->data, cap);
    if (!p) return 0;
    b->data = p;
    b->cap = cap;
    b->data[b->len] = '\0';
    return 1;
}

static int buffer_append(Buffer *b, const char *data, size_t len) {
    if (!buffer_reserve(b, len)) return 0;
    memcpy(b->data + b->len, data, len);
    b->len += len;
    b->data[b->len] = '\0';
    return 1;
}

static GSValue response_value(int status, const char *body, const char *content_type) {
    GSValue out = gs_object();
    gs_object_set(&out, "status", gs_number(status));
    gs_object_set(&out, "body", gs_string(body ? body : ""));
    gs_object_set(&out, "contentType", gs_string(content_type ? content_type : "text/plain; charset=utf-8"));
    return out;
}

static const char *mime_type(const char *path) {
    const char *dot = strrchr(path ? path : "", '.');
    if (!dot) return "application/octet-stream";

    if (!strcasecmp(dot, ".html") || !strcasecmp(dot, ".htm")) return "text/html; charset=utf-8";
    if (!strcasecmp(dot, ".css")) return "text/css; charset=utf-8";
    if (!strcasecmp(dot, ".js") || !strcasecmp(dot, ".mjs")) return "application/javascript; charset=utf-8";
    if (!strcasecmp(dot, ".json") || !strcasecmp(dot, ".map")) return "application/json; charset=utf-8";
    if (!strcasecmp(dot, ".xml")) return "application/xml; charset=utf-8";
    if (!strcasecmp(dot, ".txt") || !strcasecmp(dot, ".log")) return "text/plain; charset=utf-8";
    if (!strcasecmp(dot, ".csv")) return "text/csv; charset=utf-8";
    if (!strcasecmp(dot, ".md")) return "text/markdown; charset=utf-8";
    if (!strcasecmp(dot, ".yaml") || !strcasecmp(dot, ".yml")) return "application/yaml; charset=utf-8";
    if (!strcasecmp(dot, ".wasm")) return "application/wasm";
    if (!strcasecmp(dot, ".pdf")) return "application/pdf";
    if (!strcasecmp(dot, ".zip")) return "application/zip";
    if (!strcasecmp(dot, ".gz")) return "application/gzip";
    if (!strcasecmp(dot, ".tar")) return "application/x-tar";
    if (!strcasecmp(dot, ".7z")) return "application/x-7z-compressed";
    if (!strcasecmp(dot, ".rar")) return "application/vnd.rar";

    if (!strcasecmp(dot, ".png")) return "image/png";
    if (!strcasecmp(dot, ".jpg") || !strcasecmp(dot, ".jpeg")) return "image/jpeg";
    if (!strcasecmp(dot, ".gif")) return "image/gif";
    if (!strcasecmp(dot, ".webp")) return "image/webp";
    if (!strcasecmp(dot, ".avif")) return "image/avif";
    if (!strcasecmp(dot, ".bmp")) return "image/bmp";
    if (!strcasecmp(dot, ".tif") || !strcasecmp(dot, ".tiff")) return "image/tiff";
    if (!strcasecmp(dot, ".ico")) return "image/x-icon";
    if (!strcasecmp(dot, ".svg")) return "image/svg+xml";

    if (!strcasecmp(dot, ".mp3")) return "audio/mpeg";
    if (!strcasecmp(dot, ".wav")) return "audio/wav";
    if (!strcasecmp(dot, ".ogg")) return "audio/ogg";
    if (!strcasecmp(dot, ".oga")) return "audio/ogg";
    if (!strcasecmp(dot, ".aac")) return "audio/aac";
    if (!strcasecmp(dot, ".flac")) return "audio/flac";
    if (!strcasecmp(dot, ".m4a")) return "audio/mp4";
    if (!strcasecmp(dot, ".opus")) return "audio/opus";
    if (!strcasecmp(dot, ".weba")) return "audio/webm";

    if (!strcasecmp(dot, ".mp4")) return "video/mp4";
    if (!strcasecmp(dot, ".m4v")) return "video/x-m4v";
    if (!strcasecmp(dot, ".webm")) return "video/webm";
    if (!strcasecmp(dot, ".ogv")) return "video/ogg";
    if (!strcasecmp(dot, ".mov")) return "video/quicktime";
    if (!strcasecmp(dot, ".avi")) return "video/x-msvideo";
    if (!strcasecmp(dot, ".mkv")) return "video/x-matroska";
    if (!strcasecmp(dot, ".mpeg") || !strcasecmp(dot, ".mpg")) return "video/mpeg";
    if (!strcasecmp(dot, ".3gp")) return "video/3gpp";

    if (!strcasecmp(dot, ".woff")) return "font/woff";
    if (!strcasecmp(dot, ".woff2")) return "font/woff2";
    if (!strcasecmp(dot, ".ttf")) return "font/ttf";
    if (!strcasecmp(dot, ".otf")) return "font/otf";
    if (!strcasecmp(dot, ".eot")) return "application/vnd.ms-fontobject";

    return "application/octet-stream";
}

static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }
    long size = ftell(f);
    if (size < 0 || (unsigned long)size > GS_SERVER_MAX_BODY) {
        fclose(f);
        return NULL;
    }
    rewind(f);
    char *data = malloc((size_t)size + 1);
    if (!data) {
        fclose(f);
        return NULL;
    }
    size_t got = fread(data, 1, (size_t)size, f);
    int read_error = ferror(f);
    fclose(f);
    if (read_error) {
        free(data);
        return NULL;
    }
    data[got] = '\0';
    if (out_len) *out_len = got;
    return data;
}

static int safe_path(const char *path) {
    if (!path || path[0] != '/') return 0;
    if (strstr(path, "..")) return 0;
    if (strchr(path, '\\')) return 0;
    return 1;
}

static char *url_decode(const char *src) {
    size_t n = strlen(src);
    char *out = malloc(n + 1);
    if (!out) return NULL;
    size_t j = 0;
    for (size_t i = 0; i < n; i++) {
        if (src[i] == '%' && i + 2 < n && isxdigit((unsigned char)src[i + 1]) && isxdigit((unsigned char)src[i + 2])) {
            char hex[3] = { src[i + 1], src[i + 2], '\0' };
            out[j++] = (char)strtol(hex, NULL, 16);
            i += 2;
        } else if (src[i] == '+') {
            out[j++] = ' ';
        } else {
            out[j++] = src[i];
        }
    }
    out[j] = '\0';
    return out;
}

static char *render_text(const char *source, GSValue data) {
    if (!source) return gs_dup("");
    if (data.type != GS_OBJECT) return gs_dup(source);

    Buffer out = {0};
    const char *p = source;

    while (*p) {
        const char *open = strstr(p, "{{");
        if (!open) {
            if (!buffer_append(&out, p, strlen(p))) {
                buffer_free(&out);
                return NULL;
            }
            break;
        }

        if (!buffer_append(&out, p, (size_t)(open - p))) {
            buffer_free(&out);
            return NULL;
        }

        const char *close = strstr(open + 2, "}}");
        if (!close) {
            if (!buffer_append(&out, open, strlen(open))) {
                buffer_free(&out);
                return NULL;
            }
            break;
        }

        size_t key_len = (size_t)(close - (open + 2));
        char *key = malloc(key_len + 1);
        if (!key) {
            buffer_free(&out);
            return NULL;
        }
        memcpy(key, open + 2, key_len);
        key[key_len] = '\0';

        char *start = key;
        while (*start && isspace((unsigned char)*start)) start++;
        char *end = start + strlen(start);
        while (end > start && isspace((unsigned char)end[-1])) end--;
        *end = '\0';

        GSValue value = gs_object_get(data, start);
        const char *replacement = gs_to_cstring(value);
        if (!replacement) replacement = "";
        if (!buffer_append(&out, replacement, strlen(replacement))) {
            free(key);
            buffer_free(&out);
            return NULL;
        }
        free(key);
        p = close + 2;
    }

    if (!out.data) return gs_dup("");
    return out.data;
}

static int parse_url(const char *url, char **host, char **port, char **path) {
    if (!url || !*url) return 0;
    const char *start = NULL;
    if (!strncmp(url, "http://", 7)) start = url + 7;
    else return 0;

    const char *slash = strchr(start, '/');
    const char *authority_end = slash ? slash : start + strlen(start);
    const char *colon = NULL;
    for (const char *p = start; p < authority_end; p++) {
        if (*p == ':') colon = p;
    }

    size_t host_len = (size_t)((colon ? colon : authority_end) - start);
    if (!host_len) return 0;

    *host = malloc(host_len + 1);
    if (!*host) return 0;
    memcpy(*host, start, host_len);
    (*host)[host_len] = '\0';

    if (colon) {
        size_t port_len = (size_t)(authority_end - colon - 1);
        if (!port_len) {
            free(*host);
            *host = NULL;
            return 0;
        }
        *port = malloc(port_len + 1);
        if (!*port) {
            free(*host);
            *host = NULL;
            return 0;
        }
        memcpy(*port, colon + 1, port_len);
        (*port)[port_len] = '\0';
    } else {
        *port = gs_dup("80");
    }

    *path = gs_dup(slash ? slash : "/");
    if (!*path) {
        free(*host);
        free(*port);
        *host = *port = NULL;
        return 0;
    }
    return 1;
}

static int send_all(int fd, const char *data, size_t len) {
    size_t sent = 0;
    while (sent < len) {
        ssize_t n = send(fd, data + sent, len - sent, 0);
        if (n < 0) {
            if (errno == EINTR) continue;
            return 0;
        }
        if (n == 0) return 0;
        sent += (size_t)n;
    }
    return 1;
}

static GSValue http_request(const char *method, const char *url, const char *body, const char *content_type) {
    char *host = NULL;
    char *port = NULL;
    char *path = NULL;

    if (!parse_url(url, &host, &port, &path)) {
        return response_value(0, "Only http:// URLs are supported by libserver", "text/plain; charset=utf-8");
    }

    struct addrinfo hints;
    struct addrinfo *result = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rc = getaddrinfo(host, port, &hints, &result);
    if (rc != 0) {
        free(host); free(port); free(path);
        return response_value(0, gai_strerror(rc), "text/plain; charset=utf-8");
    }

    int fd = -1;
    for (struct addrinfo *it = result; it; it = it->ai_next) {
        fd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, it->ai_addr, it->ai_addrlen) == 0) break;
        close(fd);
        fd = -1;
    }
    freeaddrinfo(result);

    if (fd < 0) {
        free(host); free(port); free(path);
        return response_value(0, "Could not connect to HTTP server", "text/plain; charset=utf-8");
    }

    size_t body_len = body ? strlen(body) : 0;
    size_t request_size = strlen(method) + strlen(path) + strlen(host) + body_len + 1024;
    char *request = malloc(request_size);
    if (!request) {
        close(fd); free(host); free(port); free(path);
        return response_value(0, "Out of memory", "text/plain; charset=utf-8");
    }

    int written = snprintf(request, request_size,
        "%s %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n"
        "User-Agent: %s\r\n"
        "%s%s%s"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%s",
        method, path, host, GS_SERVER_VERSION,
        body_len ? "Content-Type: " : "",
        body_len ? (content_type ? content_type : "application/octet-stream") : "",
        body_len ? "\r\n" : "",
        body_len, body ? body : "");

    if (written < 0 || (size_t)written >= request_size) {
        free(request); close(fd); free(host); free(port); free(path);
        return response_value(0, "HTTP request was too large", "text/plain; charset=utf-8");
    }

    int sent_ok = send_all(fd, request, (size_t)written);
    free(request); free(host); free(port); free(path);
    if (!sent_ok) {
        close(fd);
        return response_value(0, "Could not send HTTP request", "text/plain; charset=utf-8");
    }

    Buffer raw = {0};
    if (!buffer_reserve(&raw, GS_SERVER_BUFFER)) {
        close(fd);
        return response_value(0, "Out of memory", "text/plain; charset=utf-8");
    }

    for (;;) {
        char chunk[8192];
        ssize_t n = recv(fd, chunk, sizeof(chunk), 0);
        if (n < 0) {
            if (errno == EINTR) continue;
            break;
        }
        if (n == 0) break;
        if (!buffer_append(&raw, chunk, (size_t)n)) break;
    }
    close(fd);

    if (!raw.data) return response_value(0, "Empty HTTP response", "text/plain; charset=utf-8");

    int status = 0;
    sscanf(raw.data, "HTTP/%*s %d", &status);
    char *separator = strstr(raw.data, "\r\n\r\n");
    const char *response_body = separator ? separator + 4 : "";

    const char *response_type = "text/plain; charset=utf-8";
    char *headers_end = separator;
    if (headers_end) {
        char *line = raw.data;
        while (line < headers_end) {
            char *next = strstr(line, "\r\n");
            if (!next || next > headers_end) break;
            if (!strncasecmp(line, "Content-Type:", 13)) {
                char *value = line + 13;
                while (*value == ' ' || *value == '\t') value++;
                *next = '\0';
                response_type = value;
                *next = '\r';
                break;
            }
            line = next + 2;
        }
    }

    GSValue out = response_value(status, response_body, response_type);
    buffer_free(&raw);
    return out;
}

static GSValue native_http_get(GSValue *args, int argc) {
    if (argc < 1) return response_value(0, "http_get requires a URL", "text/plain; charset=utf-8");
    return http_request("GET", gs_to_cstring(args[0]), NULL, NULL);
}

static GSValue native_http_post(GSValue *args, int argc) {
    if (argc < 1) return response_value(0, "http_post requires a URL", "text/plain; charset=utf-8");
    const char *body = argc > 1 ? gs_to_cstring(args[1]) : "";
    const char *type = argc > 2 ? gs_to_cstring(args[2]) : "application/json";
    return http_request("POST", gs_to_cstring(args[0]), body, type);
}

static GSValue native_http_put(GSValue *args, int argc) {
    if (argc < 1) return response_value(0, "http_put requires a URL", "text/plain; charset=utf-8");
    const char *body = argc > 1 ? gs_to_cstring(args[1]) : "";
    const char *type = argc > 2 ? gs_to_cstring(args[2]) : "application/json";
    return http_request("PUT", gs_to_cstring(args[0]), body, type);
}

static GSValue native_http_delete(GSValue *args, int argc) {
    if (argc < 1) return response_value(0, "http_delete requires a URL", "text/plain; charset=utf-8");
    return http_request("DELETE", gs_to_cstring(args[0]), NULL, NULL);
}

static GSValue native_http_head(GSValue *args, int argc) {
    if (argc < 1) return response_value(0, "http_head requires a URL", "text/plain; charset=utf-8");
    return http_request("HEAD", gs_to_cstring(args[0]), NULL, NULL);
}

static GSValue native_render(GSValue *args, int argc) {
    if (argc < 1) return response_value(400, "Template path is required", "text/plain; charset=utf-8");
    char *source = read_file(gs_to_cstring(args[0]), NULL);
    if (!source) return response_value(404, "Template file not found", "text/plain; charset=utf-8");
    GSValue data = argc > 1 ? args[1] : gs_object();
    char *html = render_text(source, data);
    free(source);
    if (!html) return response_value(500, "Could not render template", "text/plain; charset=utf-8");
    GSValue out = response_value(200, html, "text/html; charset=utf-8");
    free(html);
    return out;
}

static GSValue native_read_file(GSValue *args, int argc) {
    if (argc < 1) return gs_string("");
    char *data = read_file(gs_to_cstring(args[0]), NULL);
    if (!data) return gs_string("");
    GSValue out = gs_string(data);
    free(data);
    return out;
}

static GSValue native_file_exists(GSValue *args, int argc) {
    if (argc < 1) return gs_bool(0);
    return gs_bool(access(gs_to_cstring(args[0]), F_OK) == 0);
}

static GSValue native_mime(GSValue *args, int argc) {
    if (argc < 1) return gs_string("application/octet-stream");
    return gs_string(mime_type(gs_to_cstring(args[0])));
}

static void reason_phrase(int status, const char **reason) {
    switch (status) {
        case 200: *reason = "OK"; break;
        case 201: *reason = "Created"; break;
        case 204: *reason = "No Content"; break;
        case 301: *reason = "Moved Permanently"; break;
        case 302: *reason = "Found"; break;
        case 304: *reason = "Not Modified"; break;
        case 400: *reason = "Bad Request"; break;
        case 401: *reason = "Unauthorized"; break;
        case 403: *reason = "Forbidden"; break;
        case 404: *reason = "Not Found"; break;
        case 405: *reason = "Method Not Allowed"; break;
        case 408: *reason = "Request Timeout"; break;
        case 409: *reason = "Conflict"; break;
        case 413: *reason = "Payload Too Large"; break;
        case 415: *reason = "Unsupported Media Type"; break;
        case 429: *reason = "Too Many Requests"; break;
        case 500: *reason = "Internal Server Error"; break;
        case 501: *reason = "Not Implemented"; break;
        case 502: *reason = "Bad Gateway"; break;
        case 503: *reason = "Service Unavailable"; break;
        default: *reason = status >= 500 ? "Server Error" : "HTTP Response"; break;
    }
}

static int send_http(int fd, int status, const char *content_type, const char *body, int head_only) {
    const char *reason = NULL;
    reason_phrase(status, &reason);
    const char *payload = body ? body : "";
    size_t len = strlen(payload);
    char header[1024];
    int n = snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "Server: greenServe/1.0\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, HEAD, POST, PUT, PATCH, DELETE, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type, Authorization\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "\r\n",
        status, reason,
        content_type ? content_type : "text/plain; charset=utf-8", len);
    if (n <= 0 || (size_t)n >= sizeof(header)) return 0;
    if (!send_all(fd, header, (size_t)n)) return 0;
    if (!head_only && len) return send_all(fd, payload, len);
    return 1;
}

static int receive_request(int fd, Buffer *request) {
    for (;;) {
        char chunk[8192];
        ssize_t n = recv(fd, chunk, sizeof(chunk), 0);
        if (n < 0) {
            if (errno == EINTR) continue;
            return 0;
        }
        if (n == 0) break;
        if (request->len + (size_t)n > GS_SERVER_MAX_HEADER) return 0;
        if (!buffer_append(request, chunk, (size_t)n)) return 0;
        if (strstr(request->data, "\r\n\r\n")) break;
    }
    return request->data != NULL;
}

static void handle_client(int fd, const char *root) {
    Buffer request = {0};
    if (!receive_request(fd, &request)) {
        send_http(fd, 400, "text/plain; charset=utf-8", "Bad Request", 0);
        buffer_free(&request);
        return;
    }

    char method[16];
    char target[8192];
    if (sscanf(request.data, "%15s %8191s", method, target) != 2) {
        send_http(fd, 400, "text/plain; charset=utf-8", "Bad Request", 0);
        buffer_free(&request);
        return;
    }

    if (!strcmp(method, "OPTIONS")) {
        send_http(fd, 204, "text/plain; charset=utf-8", "", 0);
        buffer_free(&request);
        return;
    }

    if (strcmp(method, "GET") && strcmp(method, "HEAD")) {
        send_http(fd, 405, "text/plain; charset=utf-8", "Method Not Allowed", 0);
        buffer_free(&request);
        return;
    }

    char *query_start = strchr(target, '?');
    char *fragment = strchr(target, '#');
    if (fragment) *fragment = '\0';
    if (query_start) *query_start = '\0';

    char *decoded = url_decode(target);
    if (!decoded || !safe_path(decoded)) {
        free(decoded);
        send_http(fd, 403, "text/plain; charset=utf-8", "Forbidden", 0);
        buffer_free(&request);
        return;
    }

    if (!strcmp(decoded, "/")) {
        free(decoded);
        decoded = gs_dup("/index.html");
    }

    char full[8192];
    int path_written = snprintf(full, sizeof(full), "%s%s", root, decoded);
    free(decoded);
    if (path_written < 0 || (size_t)path_written >= sizeof(full)) {
        send_http(fd, 414, "text/plain; charset=utf-8", "URI Too Long", 0);
        buffer_free(&request);
        return;
    }

    struct stat st;
    if (stat(full, &st) != 0) {
        send_http(fd, 404, "text/plain; charset=utf-8", "Not Found", 0);
        buffer_free(&request);
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        size_t index_len = strlen(full) + strlen("/index.html") + 1;
        char *index = malloc(index_len);
        if (!index) {
            send_http(fd, 500, "text/plain; charset=utf-8", "Out of Memory", 0);
            buffer_free(&request);
            return;
        }
        snprintf(index, index_len, "%s/index.html", full);
        size_t index_file_len = 0;
        char *index_data = read_file(index, &index_file_len);
        if (index_data) {
            send_http(fd, 200, mime_type(index), index_data, !strcmp(method, "HEAD"));
            free(index_data);
            free(index);
            buffer_free(&request);
            return;
        }
        free(index);
        send_http(fd, 403, "text/plain; charset=utf-8", "Directory listing is disabled", 0);
        buffer_free(&request);
        return;
    }

    size_t len = 0;
    char *data = read_file(full, &len);
    if (!data) {
        send_http(fd, 500, "text/plain; charset=utf-8", "Could not read file", 0);
        buffer_free(&request);
        return;
    }

    send_http(fd, 200, mime_type(full), data, !strcmp(method, "HEAD"));
    free(data);
    buffer_free(&request);
}

static GSValue native_serve(GSValue *args, int argc) {
    int port = argc > 0 ? (int)gs_to_number(args[0]) : 8080;
    const char *root = argc > 1 ? gs_to_cstring(args[1]) : ".";
    if (port < 1 || port > 65535) return response_value(0, "Invalid port", "text/plain; charset=utf-8");

    struct stat st;
    if (stat(root, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return response_value(0, "Static root directory does not exist", "text/plain; charset=utf-8");
    }

    signal(SIGPIPE, SIG_IGN);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) return response_value(0, strerror(errno), "text/plain; charset=utf-8");

    int yes = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons((uint16_t)port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 || listen(server_fd, GS_SERVER_BACKLOG) < 0) {
        const char *message = strerror(errno);
        close(server_fd);
        return response_value(0, message, "text/plain; charset=utf-8");
    }

    printf("greenServe HTTP server listening on http://127.0.0.1:%d\n", port);
    fflush(stdout);

    for (;;) {
        int client = accept(server_fd, NULL, NULL);
        if (client < 0) {
            if (errno == EINTR) continue;
            break;
        }
        handle_client(client, root);
        close(client);
    }

    close(server_fd);
    return gs_null();
}

static const GSNativeFunction server_functions[] = {
    {"http_get", native_http_get},
    {"http_post", native_http_post},
    {"http_put", native_http_put},
    {"http_delete", native_http_delete},
    {"http_head", native_http_head},
    {"render", native_render},
    {"read_file", native_read_file},
    {"file_exists", native_file_exists},
    {"mime_type", native_mime},
    {"serve", native_serve}
};

static GSModule server_module = {
    "server",
    server_functions,
    sizeof(server_functions) / sizeof(server_functions[0])
};

GSModule *green_module_init(void) {
    return &server_module;
}
