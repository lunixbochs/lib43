#include "syscall.h"

abi_long _write(int fd, const void *buf, abi_long len);
abi_long _read(int fd, const void *buf, abi_long len);
void *_mmap(void *addr, abi_long len, int prot, int flags, int fd, abi_long off);
int _munmap(void *addr, abi_long len);
void _exit(int status);
