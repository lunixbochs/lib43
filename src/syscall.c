#include <sys/syscall.h>
#include "syscall.h"

#ifdef __APPLE__
#  define SYS(name) (SYS_##name + 0x2000000)
#else
#  define SYS(name) SYS_##name
#endif

#if defined(__APPLE__) || defined(__linux__)
#  ifdef __LP64__
#    define SYSCALL_CLOBBER "rcx", "r10", "r11"
#    ifdef __linux__
#      define SYSCALL_ASM "mov %0, %%rax; mov %%rcx, %%r10; syscall;"
#    else
#      define SYSCALL_ASM "mov %0, %%rax; syscall;"
#    endif
#  else
#    ifdef __linux__
#      define SYSCALL_ASM ""
#    else
#      define SYSCALL_ASM "movl %0, %%eax; int $0x80;"
#      define SYSCALL_CLOBBER "eax"
#    endif
#  endif
#else
#  error "Unsupported arch."
#endif

#ifndef SYSCALL_ASM
#  error "Unsupported OS."
#endif

// 32-bit ABI uses the stack for functions, but registers for kernel
// so our normal approach is useless here
#if defined(__linux__) && !defined(__LP64__)
#define arg abi_long
#define sys(name) \
   abi_long name(arg a1, arg a2, arg a3, arg a4, arg a5, arg a6) { \
       register abi_long eax __asm__("eax"), ebp __asm__("ebp");   \
       ebp = a6;                                                   \
       __asm__ __volatile__(                                       \
           "int $0x80;"                                            \
           :"=a"(eax)                                              \
           :"a"(SYS(name)), "b"(a1), "c"(a2), "d"(a3), "S"(a4), "D"(a5) \
       );                                                          \
       return eax;                                                 \
   }
#else
#define sys(name)            \
   abi_long name() {         \
       abi_long ret;         \
       __asm__ __volatile__( \
           SYSCALL_ASM       \
           ::"i"(SYS(name))  \
           :SYSCALL_CLOBBER  \
       );                    \
       return ret;           \
   }
#endif

#include "syscall.list"
