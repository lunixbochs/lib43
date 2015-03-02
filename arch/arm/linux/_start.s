.text
.global _start
_start:
    ldr %r0, [%sp]
    add %r1, %sp, #4
    sub %lr, %lr, %lr
    bl main
    push {%r0}
    ldr %r1, =stdout
    ldr %r0, [%r1]
    bl fflush
    pop {%r0}
    bl _exit
