.global _syscall
_syscall:
    mov 28(%esp), %eax
    int $0x80
    ret
