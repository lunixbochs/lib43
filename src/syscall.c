#include <sys/syscall.h>

/* Apple support is x86_64 only */
#if defined(__APPLE__)
#define sys(name) \
    int name() {  \
        __asm__ __volatile__(       \
            "movq %0, %%rax;"       \
            "syscall;"              \
            ::"i"(SYS_##name + 0x2) \
            :"rax"                  \
       );                           \
    }
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
