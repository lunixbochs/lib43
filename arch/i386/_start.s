.text
.global _start
_start:
    xor %ebp, %ebp
    pop %ecx
    mov %esp, %eax
    and $-16, %esp
    push %eax
    push %ecx
    call main

    push %eax
    call exit

    push stdout
    call fflush
    pop %ecx

    call exit
