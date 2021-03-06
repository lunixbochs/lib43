#include "mem.h"
#include "mman.h"
#include "syscalls.h"

#include <sys/mman.h>

#if !defined(MAP_ANONYMOUS)
#  ifdef __linux__
#    define MAP_ANONYMOUS 0x20
#  elif defined(__APPLE__) || defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#    define MAP_ANONYMOUS 0x1000
#  endif
#endif

#define mmap_malloc(addr, size) _mmap(addr, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0)

void *calloc(size_t count, size_t size) {
    void *p = malloc(count * size);
    if (p == 0) return 0;
    memset(p, '\0', count * size);
    return p;
}

void *malloc(size_t size) {
#ifdef __mips__
    void *pos = _brk(0);
    _brk(pos + size + sizeof(size_t));
    *(size_t *)pos = size;
    return (void *)pos + sizeof(size_t);
#else
    size += sizeof(size_t);
    void *p = mmap_malloc(0, size);
    if (p == 0) return 0;
    *(size_t *)p = size;
    return p + sizeof(size_t);
#endif
}

void *realloc(void *p, size_t new_size) {
    if (p == 0) {
        return malloc(new_size);
    }
    // really need to use a struct + helpers. this is so prone to human error.
    void *origin = p - sizeof(size_t);
    size_t old_size = *(size_t *)origin;
#ifdef __mips__
    void *new = malloc(new_size);
    memcpy(new, p, old_size);
    return new;
#endif
    // if you realloc more than 31/63 bits more, you should *really* just do a malloc
    off_t diff = new_size - old_size;
    if (new_size > old_size) {
        // tried alignment + mmap, but it always made a split allocation
        // so I can't zero-cost realloc unless I preallocate+split like a real allocator
        void *new = malloc(new_size);
        memcpy(new, p, old_size - sizeof(size_t));
        free(p);
        return new;
    } else if (new_size < old_size) {
        _munmap(origin + old_size, diff);
        *(size_t *)origin = new_size;
    }
    return p;
}

void free(void *p) {
#ifndef __mips__
    if (p != 0) {
        p -= sizeof(size_t);
        size_t size = *(size_t *)p;
        _munmap(p, size);
    }
#endif
}
