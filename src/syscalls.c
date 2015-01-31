#include "syscalls.h"

abi_long _write(int fd, const void *buf, abi_long len) {
    return syscall3(SYS_write, fd, buf, len);
}
abi_long _read(int fd, const void *buf, abi_long len) {
    return syscall3(SYS_read, fd, buf, len);
}
void *_mmap(void *addr, abi_long len, int prot, int flags, int fd, abi_long off) {
    return (void *)syscall6(SYS_mmap, addr, len, prot, flags, fd, off);
}
int _munmap(void *addr, abi_long len) {
    return syscall2(SYS_munmap, addr, len);
}
void _exit(int status) {
    syscall1(SYS_exit, status);
}
