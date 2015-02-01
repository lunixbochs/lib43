#include "mem.h"
#include "mman.h"
#include "syscalls.h"

#include <sys/mman.h>

#if !defined(MAP_ANONYMOUS) && defined(__linux__)
#define MAP_ANONYMOUS 0x20
#elif defined(__APPLE__)
#define MAP_ANONYMOUS 0x1000
#endif

#define mmap_malloc(addr, size) _mmap(addr, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)

void *calloc(size_t count, size_t size) {
    void *p = malloc(count * size);
    if (p == 0) return 0;
    memset(p, '\0', count * size);
    return p;
}

void *malloc(size_t size) {
    size += sizeof(size_t);
    void *p = mmap_malloc(0, size);
    if (p == 0) return 0;
    *(size_t *)p = size;
    return p + sizeof(size_t);
}

void *realloc(void *p, size_t new_size) {
    size_t old_size = *(size_t *)(p - sizeof(size_t));
    if (new_size > old_size) {
        void *extra = mmap_malloc(p + old_size, new_size - old_size);
        if (extra != 0) {
            *(size_t *)(p - sizeof(size_t)) = new_size;
        }
        return p;
    } else if (new_size < old_size) {
        _munmap(p + old_size, old_size - new_size);
    }
    return p;
}

void free(void *p) {
    if (p != 0) {
        p -= sizeof(size_t);
        size_t size = *(size_t *)p;
        _munmap(p, size);
    }
}
