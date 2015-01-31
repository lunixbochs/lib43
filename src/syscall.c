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
#    ifndef __linux__
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

#include "syscall.list"
