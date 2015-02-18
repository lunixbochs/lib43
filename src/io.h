#include <sys/types.h>

#define BUFSIZE 4096

#define FD_FILE 1
#define FD_STR 2

typedef struct {
    int fd, pos, size, type;
    char buf[BUFSIZE];
} FILE;

extern FILE *stderr;
extern FILE *stdin;
extern FILE *stdout;

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *f);
int fflush(FILE *f);
int fgetc(FILE *f);
int fputc(int c, FILE *f);
int fseek(FILE *f, long offset, int whence);
int printf(const char *fmt, ...);
int putc(int c, FILE *f);
int puts(const char *s);
size_t fread(char *d, size_t size, size_t count, FILE *f);
size_t fwrite(const char *s, size_t size, size_t count, FILE *f);
