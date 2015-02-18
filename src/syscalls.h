#include <sys/types.h>

size_t _write(int fd, const void *buf, size_t len);
size_t _read(int fd, const void *buf, size_t len);
void *_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t off);
int _munmap(void *addr, size_t len);
void _exit(int status);
off_t _lseek(int fd, off_t offset, int whence);
int _open(const char *path, int flags, ...);
int _close(int fd);
