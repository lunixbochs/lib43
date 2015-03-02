#ifndef SYSCALL_H
#define SYSCALL_H

#include "errno.h"

#include <stdint.h>
#include <sys/syscall.h>

#if defined(__APPLE__) && defined(__LP64__)
#  define SYS(name) (SYS_##name + 0x2000000)
#else
#  define SYS(name) SYS_##name
#endif

#if defined(__x86_64)
typedef int64_t abi_long;
#elif defined(__i386__) || defined(__mips__) || defined(__arm__)
typedef int32_t abi_long;
#endif

extern abi_long syscall(int n, abi_long a1, abi_long a2, abi_long a3, abi_long a4, abi_long a5, abi_long a6);

#define syscall6(n, a1, a2, a3, a4, a5, a6)                             \
    ({                                                                  \
        errno = 0;                                                      \
        (abi_long)syscall((abi_long)a1, (abi_long)a2, (abi_long)a3,     \
                          (abi_long)a4, (abi_long)a5, (abi_long)a6, n); \
    })
#define syscall5(n, args...) syscall6(n, args, 0)
#define syscall4(n, args...) syscall5(n, args, 0)
#define syscall3(n, args...) syscall4(n, args, 0)
#define syscall2(n, args...) syscall3(n, args, 0)
#define syscall1(n, args...) syscall2(n, args, 0)
#define syscall0(n) syscall1(n, 0)

#endif // SYSCALL_H
