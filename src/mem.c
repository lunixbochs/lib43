int memcmp(const void *p1, const void *p2, int num) {
    char *c1 = (char *)p1;
    char *c2 = (char *)p2;
    for (int i = 0; i < num; i++) {
        if (*c1 < *c2) {
            return -1;
        } else if (*c1 > *c2) {
            return 1;
        }
    }
    return 0;
}

void *memchr(const void *ptr, int c, int n) {
    unsigned const char *cptr = ptr;
    for (int i = 0; i < n; i++) {
        if (cptr[i] == c) {
            return (void *)cptr+i;
        }
    }
    return 0;
}

void *memcpy(void *dst, const void *src, int num) {
    char *cdst = dst;
    const char *csrc = src;
    for (int i = 0; i < num; i++) {
        *cdst++ = *csrc++;
    }
    return dst;
}

void *memmove(void *dst, const void *src, int num) {
    return memcpy(dst, src, num);
}

void *memset(void *ptr, int val, int num) {
    unsigned char *cptr = ptr;
    for (int i = 0; i < num; i++) {
        *cptr++ = val;
    }
    return ptr;
}
