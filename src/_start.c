#include "syscall.h"
#include "io.h"

extern int main();

void _start() {
    int ret;
    __asm__ __volatile__ (
         "pop %%rbp;" // C compiler will push rbp
         "pop %%rdi;"        // argc
         "mov %%rsp, %%rsi;" // argv
         "andq $-16, %%rsp;"
         "call main;"
         :"=r"(ret)
    );
    fflush(stdout);
    exit(ret);
}
