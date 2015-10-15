#include <sys/types.h>

int memcmp(const void *p1, const void *p2, size_t len);
void *memchr(const void *ptr, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t len);
void *memmove(void *dst, const void *src, size_t len);
void *memset(void *ptr, int val, size_t len);
