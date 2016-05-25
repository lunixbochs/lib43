#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include "stdlib.h"
#include "syscalls.h"

static FILE _stderr = {.fd = 2};
static FILE _stdin = {.fd = 0};
static FILE _stdout = {.fd = 1};
FILE *stderr = &_stderr;
FILE *stdin = &_stdin;
FILE *stdout = &_stdout;

static void freset(FILE *f) {
    f->size = 0;
    f->pos = 0;
    memset(f->buf, 0, BUFSIZE);
}

static int buf_seek(FILE *f, long offset, int whence) {
    f->size = 0;
    off_t pos = _lseek(f->fd, offset, whence);
    if (pos >= 0) {
        f->pos = pos;
    }
    return pos;
}

static int buf_write(FILE *f, const char *s, int len) {
    if (len == 0) {
        return fflush(f) - f->size;
    }
    // TODO: EOF + error handling
    if ((len + f->size) > BUFSIZE) {
        fflush(f);
        return _write(f->fd, s, len);
    }
    memcpy(f->buf + f->size, s, len);
    f->size += len;
    if (memchr(f->buf, '\n', f->size) != 0) {
        return fflush(f) - f->size;
    }
    return len;
}

static int buf_read(FILE *f, char *d, int len) {
    // TODO: EOF + error handling
    int ret = 0;
    int size = f->size - f->pos;
    char *pos = f->buf + f->pos;
    int count;
    // TODO: handle len > bufsize
    if (size > 0) {
        if (len < size) count = len;
        else            count = size;
        memcpy(d, pos, count);
        d += count;
        ret += count;
        len -= count;
        size -= count;
        if (count < size) {
            f->pos += count;
            pos += count;
        } else {
            freset(f);
            pos = f->buf;
        }
    }
    if (len > BUFSIZE) {
        // TODO: error precedence over length?
        return ret + _read(f->fd, d, len);
    } else if (len > 0) {
        count = _read(f->fd, pos, BUFSIZE);
        if (count < 0) {
            return count;
        } else if (count == 0) {
            if (ret > 0) return ret;
            else         return -1;
        } else if (count > len) {
            memcpy(d, pos, len);
            memmove(f->buf, pos + len, count - len);
            f->size = count - len;
            return ret + len;
        } else {
            memcpy(d, pos, count);
            return ret + count;
        }
    }
    return ret;
}

FILE *fopen(const char *path, const char *mode) {
    int mask;
    switch (mode[0]) {
        case 'r':
            mask = O_RDONLY;
            if (mode[1] == '+') // r+
                mask = O_RDWR;
            break;
        case 'w':
            mask = O_WRONLY;
            if (mode[1] == '+') // w+
                mask = O_RDWR | O_CREAT | O_TRUNC;
            break;
        case 'a':
            mask = O_WRONLY | O_APPEND | O_CREAT;
            if (mode[1] == '+') // a+
                mask = O_RDWR | O_APPEND | O_CREAT;
            break;
        default:
            return 0;
    }
    // TODO: source this from somewhere real
    mode_t perm = 0600;
    int fd = _open(path, mask, perm);
    if (fd < 0) {
        return 0;
    }
    FILE *f = malloc(sizeof(FILE));
    f->fd = fd;
    f->pos = 0;
    f->size = 0;
    f->type = FD_FILE;
    return f;
}

int fclose(FILE *f) {
    fflush(f);
    _close(f->fd);
    free(f);
    // TODO: error checking
    return 0;
}

int fseek(FILE *f, long offset, int whence) {
    return buf_seek(f, offset, whence);
}

size_t fread(char *d, size_t size, size_t count, FILE *f) {
    return buf_read(f, d, size * count);
}

size_t fwrite(const char *s, size_t size, size_t count, FILE *f) {
    return buf_write(f, s, size * count);
}

int fflush(FILE *f) {
    if (f->size == 0) return 0;
    int ret = _write(f->fd, f->buf, f->size);
    freset(f);
    return ret;
}

int fgetc(FILE *f) {
    char c;
    int ret = buf_read(f, &c, 1);
    if (ret < 1) return -1;
    return (unsigned char)c;
}

int fputc(int c, FILE *f) {
    char _c = c;
    return buf_write(f, &_c, 1);
}

int putc(int c, FILE *f) {
    return fputc(c, f);
}

int puts(const char *s) {
    return buf_write(stdout, s, strlen(s));
}

int printf(const char *fmt, ...) {
#define arg(type) va_arg(params, type)
    const char *pos = fmt;
    char c;
    int control = false;

    va_list params;
    va_start(params, fmt);
    while ((c = *pos++) != 0) {
        if (control) {
            control = false;
            // TODO: implement padding controls
            if (c >= '0' && c <= '9') {
                control = true;
                continue;
            }
            switch (c) {
                case '%':
                    putc(c, stdout);
                    break;
                case 'c':
                    putc(arg(int), stdout);
                    break;
                case 's': {
                    char *s = arg(char *);
                    if (s == NULL) {
                        puts("(null)");
                    } else {
                        puts(s);
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    puts(itoa_signed(arg(int), 10));
                    break;
                }
                case 'u':
                    puts(itoa(arg(int), 10));
                    break;
                case 'p':
                case 'x':
                    puts(itoa(arg(int), 16));
                    break;
                case 'X':
                    puts(strupr(itoa(arg(int), 16)));
                    break;
            }
        } else if (c == '%') {
            control = true;
        } else {
            putc(c, stdout);
        }
    }
    va_end(params);
#undef arg
    return 0;
}
