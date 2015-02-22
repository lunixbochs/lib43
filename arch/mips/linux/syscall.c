#include "syscall.h"

#define arg abi_long
#define reg(name) register abi_long name __asm__(#name)
arg syscall(arg _1, arg _2, arg _3, arg _4, arg _5, arg _6, int n) {
    reg(v0) = n; reg(a0) = _1; reg(a1) = _2; reg(a2) = _3;
    reg(a4) = _4; reg(a5) = _5; reg(a6) = _6;
    __asm__ __volatile__(
        "syscall;"
        :"=r"(v0)
        :"r"(v0), "r"(a0), "r"(a1), "r"(a2), "r"(a4), "r"(a5),  "r"(a6)
    );
    return v0;
}
