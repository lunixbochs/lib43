.text
.global _start
_start:
    pop %ecx
    and $-16, %esp
    push %esp
    push %ecx
    call main

    push %eax

    push stdout
    call fflush

    call exit
