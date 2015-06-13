#include <fcntl.h>
#include <stdarg.h>

#include "syscall.h"
#include "syscalls.h"

size_t _write(int fd, const void *buf, size_t len) {
    return syscall3(SYS(write), fd, buf, len);
}
size_t _read(int fd, const void *buf, size_t len) {
    return syscall3(SYS(read), fd, buf, len);
}
void *_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t off) {
#ifdef SYS_mmap2
    int num = SYS(mmap2);
#else
    int num = SYS(mmap);
#endif
    abi_long ret = syscall6(num, addr, len, prot, flags, fd, off);
    if (ret == -1) {
        return (void *)0;
    }
    return (void *)ret;
}
int _munmap(void *addr, size_t len) {
    return syscall2(SYS(munmap), addr, len);
}
int _mprotect(void *addr, size_t len, int prot) {
    return syscall3(SYS(mprotect), addr, len, prot);
}
void _exit(int status) {
    (void)syscall1(SYS(exit), status);
}
off_t _lseek(int fd, off_t offset, int whence) {
    return syscall2(SYS(lseek), offset, whence);
}
int _open(const char *path, int flags, ...) {
    va_list arg;
    va_start(arg, flags);
    mode_t mode = 0;
    if (flags & O_CREAT) {
        mode = va_arg(arg, int);
    }
    va_end(arg);
    return syscall3(SYS(open), path, flags, mode);
}
int _close(int fd) {
    return syscall1(SYS(close), fd);
}
#ifdef SYS_brk
void *_brk(void *addr) {
    return (void *)syscall1(SYS(brk), addr);
}
#endif
int _ptrace(int request, pid_t pid, uintptr_t addr, int data) {
    return syscall4(SYS(ptrace), request, pid, addr, data);
}
