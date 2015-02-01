#include "io.h"
#include "syscalls.h"

#include <sys/mman.h>

#if !defined(MAP_ANONYMOUS) && defined(__linux__)
#define MAP_ANONYMOUS 0x20
#elif defined(__APPLE__)
#define MAP_ANONYMOUS 0x1000
#endif

void *malloc(size_t size) {
    size += sizeof(size_t);
    printf("%d, %d, %d, %d, %d, %d\n", 0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    void *p = _mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (p == 0) {
        return 0;
    }
    *(size_t *)p = size;
    return p + sizeof(size_t);
}

void *free(void *p) {
    if (p != 0) {
        p -= sizeof(size_t);
        size_t size = *(size_t *)p;
        _munmap(p, size);
    }
}
