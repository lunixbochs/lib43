#include "syscalls.h"

abi_long _write(int fd, const void *buf, abi_long len) {
    return syscall3(SYS(write), fd, buf, len);
}
abi_long _read(int fd, const void *buf, abi_long len) {
    return syscall3(SYS(read), fd, buf, len);
}
void *_mmap(void *addr, abi_long len, int prot, int flags, int fd, abi_long off) {
    int num = SYS(mmap);
#ifdef SYS_mmap2
    num = SYS(mmap2);
#endif
    return (void *)syscall6(num, addr, len, prot, flags, fd, off);
}
int _munmap(void *addr, abi_long len) {
    return syscall2(SYS(munmap), addr, len);
}
void _exit(int status) {
    syscall1(SYS(exit), status);
}
