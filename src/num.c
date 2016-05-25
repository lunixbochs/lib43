#include "num.h"

static const char *digits = "0123456789abcdef";

char *itoa(unsigned int i, int base) {
    if (base < 0 || base > 16) {
        return "(invalid base)";
    }
    static char buf[12] = {0};
    char *pos = &buf[11];
    do {
        *--pos = (char)digits[i % base];
        i /= base;
    } while (i > 0);
    return pos;
}

char *itoa_signed(int i, int base) {
    if (i < 0) {
        char *tmp = itoa(-i, base);
        if (tmp[0] == '(' || tmp[0] == '\0') {
            return tmp;
        }
        *--tmp = '-';
        return tmp;
    } else {
        return itoa(i, base);
    }
}

int atoi(char *str) {
    int i = 0;
    char c;
    while ((c = *str++) != '\0') {
        if (c >= '0' && c <= '9') {
            i *= 10;
            i += (c - 48);
        }
    }
    return i;
}
