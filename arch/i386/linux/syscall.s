.global syscall
syscall:
    push %ebx
    push %ecx
    push %edx
    push %esi
    push %edi

    add $24, %esp
    pop %eax
    pop %ebx
    pop %ecx
    pop %edx
    pop %esi
    pop %edi
    int $0x80

    sub $48, %esp
    pop %edi
    pop %esi
    pop %edx
    pop %ecx
    pop %ebx
    ret
