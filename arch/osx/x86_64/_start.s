.text
.globl start
start:
    pop %rdi
    mov %rsp, %rsi
    and $-16, %rsp
    call _main
    push %rax
    mov _stdout@GOTPCREL(%rip), %rdi
    call _fflush
    pop %rdi
    call __exit
