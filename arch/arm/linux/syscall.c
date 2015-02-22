#include "syscall.h"

#define arg abi_long
#define reg(name) register abi_long name __asm__(#name)
arg syscall(arg _1, arg _2, arg _3, arg _4, arg _5, arg _6, int n) {
    reg(r7) = n; reg(r0) = _1; reg(r1) = _2; reg(r2) = _3;
    reg(r3) = _4; reg(r4) = _5; reg(r5) = _6;
    __asm__ __volatile__(
        "SVC #0"
        :"=r"(r0)
        :"r"(r7), "r"(r0), "r"(r1), "r"(r2), "r"(r3), "r"(r4),  "r"(r5)
    );
    return r0;
}
