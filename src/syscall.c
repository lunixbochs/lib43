#include <sys/syscall.h>
#include "syscall.h"

#ifdef __APPLE__
#  define SYS(name) (SYS_##name + 0x2000000)
#else
#  define SYS(name) SYS_##name
#endif

#define reg(name) register abi_long name __asm__(#name)
#if defined(__linux__) || defined(__APPLE__)
#  ifdef __LP64__
#    define SYSCALL_PREFIX reg(rax) = n; reg(rdi) = a1; reg(rsi) = a2; reg(rdx) = a3; \
                                         reg(r10) = a4; reg(r8)  = a5; reg(r9)  = a6;
#    define SYSCALL_ASM "syscall;"
#    define SYSCALL_SUFFIX :"=r"(rax)                               \
                           :"r"(rax), "r"(rdi), "r"(rsi), "r"(rdx), \
                                      "r"(r10), "r"(r8),  "r"(r9)   \
                           :"rcx", "r11"
#    define SYSCALL_RET return rax;
#  else
#    define SYSCALL_PREFIX reg(eax) = n; reg(ebp) = a5;
#    define SYSCALL_ASM "int $0x80;"
#    define SYSCALL_SUFFIX :"=r"(eax) \
                           :"r"(eax), "b"(a1), "c"(a2), "d"(a3), "S"(a4), "D"(a5)
#    define SYSCALL_RET return eax;
#  endif
#endif

#ifndef SYSCALL_ASM
#  error "Unsupported OS."
#endif

#define arg abi_long
arg syscall(int n, arg a1, arg a2, arg a3, arg a4, arg a5, arg a6) {
    SYSCALL_PREFIX
    __asm__ __volatile__(
        SYSCALL_ASM
        SYSCALL_SUFFIX
    );
    SYSCALL_RET
}
