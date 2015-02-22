.text
.global start
start:
    xor %ebp, %ebp
    pop %ecx
    mov %esp, %eax
    and $-16, %esp
    push %eax
    push %ecx
    call _main
    push %eax

    push _stdout
    call _fflush
    pop %ecx

    call __exit
