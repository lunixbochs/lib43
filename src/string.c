#include "string.h"
#include "ctype.h"

size_t strlen(const char *s1) {
    size_t i = 0;
    do i++; while (s1[i] != '\0');
    return i;
}

char *strcpy(char *dst, const char *src) {
    char *out = dst;
    do *out++ = *src; while (*src++ != '\0');
    return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
    size_t i = 0;
    do dst[i] = *src; while (*src++ != '\0' && i++ < n);
    return dst;
}

char *strcat(char *s1, const char *s2) {
    strcpy(s1 + strlen(s1), s2);
    return s1;
}

char *strncat(char *s1, const char *s2, size_t n) {
    strncpy(s1 + strlen(s1), s2, n);
    return s1;
}

char *strupr(char *s1) {
    do *s1 = toupper(*s1); while (*s1++ != '\0');
    return s1;
}
