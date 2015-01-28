#include <stdarg.h>
#include <stdbool.h>

#include "stdlib.h"
#include "syscall.h"

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

static int buf_write(FILE *f, const char *s, int len) {
    // TODO: EOF + error handling
    if ((len + f->size) > BUFSIZE) {
        fflush(f);
        return write(f->fd, s, len);
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
        return ret + read(f->fd, d, len);
    } else if (len > 0) {
        count = read(f->fd, pos, BUFSIZE);
        if (count < 0) {
            return count;
        } else if (count == 0) {
            if (ret > 0) return ret;
            else         return -1;
        } else if (count > len) {
            memcpy(d, pos, len);
            memmove(f->buf, f->buf + len, count);
            f->size = count - len;
            return ret + len;
        } else {
            memcpy(d, f->buf, count);
            freset(f);
            return ret + count;
        }
    }
}

int fflush(FILE *f) {
    if (f->size == 0) return 0;
    int ret = write(f->fd, f->buf, f->size);
    freset(f);
    return ret;
}

int fgetc(FILE *f) {
    unsigned char c;
    int ret = buf_read(f, &c, 1);
    if (ret < 1) return -1;
    return c;
}

int fputc(int c, FILE *f) {
    unsigned char _c = c;
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
                case 's':
                    puts(arg(char *));
                    break;
                case 'd':
                case 'i': {
                    int i = arg(int);
                    if (i < 0) {
                        i = (i ^ -1) + 1;
                        puts("-");
                    }
                    puts(itoa(i, 10));
                    break;
                }
                case 'u':
                    puts(itoa(arg(int), 10));
                    break;
                case 'x':
                    puts(itoa(arg(int), 16));
                    break;
                case 'X':
                    puts(strupr(itoa(arg(int), 16)));
                    break;
                case 'p':
                    puts(itoa(arg(int), 10));
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
}
