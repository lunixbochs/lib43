#include <stdarg.h>
#include <stdbool.h>

#include "stdlib.h"
#include "syscall.h"

static int putc(int c) {
    return write(1, &c, 1);
}

static int puts(const char *s) {
    return write(1, s, strlen(s));
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
                    putc(c);
                    break;
                case 'c':
                    putc(arg(int));
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
            putc(c);
        }
    }
    va_end(params);
#undef arg
}
