#include "syscall.h"
#include "io.h"

void _start() {
    static abi_long ret;
    __asm__ __volatile__ (
#ifdef __LP64__
         "pop %%rbp;"
         "pop %%rdi;"
         "mov %%rsp, %%rsi;"
         "and $-16, %%rsp;"
         "call main;"
         "mov %%rax, %0;"
#else
         "leave;"
         "pop %%ecx;"
         "and $-16, %%esp;"
         "push %%esp;"
         "push %%ecx;"
         "call main;"
         "mov %%eax, %0;"
#endif
         :"=r"(ret)
    );
    fflush(stdout);
    exit(ret);
}
