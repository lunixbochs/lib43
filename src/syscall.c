#include <sys/syscall.h>
#include "syscall.h"

#ifdef __APPLE__
#  define SYS(name) (SYS_##name + 0x2000000)
#else
#  define SYS(name) SYS_##name
#endif

#define reg(name) register abi_long name __asm__(#name)
#if defined(__linux__) || defined(__APPLE__)
#  ifdef __x86_64__
#    define SYSCALL_PREFIX reg(rax) = n; reg(rdi) = _1; reg(rsi) = _2; reg(rdx) = _3; \
                                         reg(r10) = _4; reg(r8)  = _5; reg(r9)  = _6;
#    define SYSCALL_ASM "syscall;"
#    define SYSCALL_SUFFIX :"=r"(rax)                               \
                           :"r"(rax), "r"(rdi), "r"(rsi), "r"(rdx), \
                                      "r"(r10), "r"(r8),  "r"(r9)   \
                           :"rcx", "r11"
#    define SYSCALL_RET return rax;
#  elif defined(__i386__)
#    define SYSCALL_PREFIX reg(eax) = n; reg(ebp) = _5;
#    define SYSCALL_ASM "int $0x80;"
#    define SYSCALL_SUFFIX :"=r"(eax) \
                           :"r"(eax), "b"(_1), "c"(_2), "d"(_3), "S"(_4), "D"(_5)
#    define SYSCALL_RET return eax;
#  elif defined(__mips__)
#    define SYSCALL_PREFIX reg(v0) = n; reg(a0) = _1; reg(a1) = _2; reg(a2) = _3; \
                                        reg(a4) = _4; reg(a5) = _5; reg(a6) = _6;
#    define SYSCALL_ASM "syscall;"
#    define SYSCALL_SUFFIX :"=r"(v0)
#    define SYSCALL_RET return v0;
#  endif
#endif

#ifndef SYSCALL_ASM
#  error "Unsupported OS/arch."
#endif

#define arg abi_long
arg syscall(int n, arg _1, arg _2, arg _3, arg _4, arg _5, arg _6) {
    SYSCALL_PREFIX
    __asm__ __volatile__(
        SYSCALL_ASM
        SYSCALL_SUFFIX
    );
    SYSCALL_RET
}
