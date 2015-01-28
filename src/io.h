#define BUFSIZE 4096

typedef struct {
    int fd, pos, size;
    char buf[BUFSIZE];
} FILE;

extern FILE *stderr;
extern FILE *stdin;
extern FILE *stdout;

int fflush(FILE *f);
int fgetc(FILE *f);
int fputc(int c, FILE *f);
int printf(const char *fmt, ...);
int putc(int c, FILE *f);
int puts(const char *s);
