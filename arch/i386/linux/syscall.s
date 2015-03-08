.global syscall
syscall:
    push %ebx
    push %ecx
    push %edx
    push %esi
    push %edi
    push %ebp

    add $28, %esp
    pop %ebx
    pop %ecx
    pop %edx
    pop %esi
    pop %edi
    pop %ebp
    pop %eax
    int $0x80

    sub $56, %esp
    pop %ebp
    pop %edi
    pop %esi
    pop %edx
    pop %ecx
    pop %ebx
    ret
