#include <sys/syscall.h>

#if defined(__APPLE__)
#error "osx"
#elif defined(__linux__)
#define sys(name) \
    int name() {  \
        __asm__ __volatile__( \
            "movq %0, %%rax;" \
            "syscall;"        \
            ::"i"(SYS_##name) \
            :"rax"            \
        );                    \
    }
#else
#error "unsupported architecture"
#endif

#include "syscall.list"
