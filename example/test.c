#include <math.h>
#include <unistd.h>
#include "stdlib.h"

int main(int argc, char **argv) {
    printf("hello with printf: %s\n", "world");
    printf("args (%d):\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("  %d @0x%p = \"%s\"\n", i, argv[i], argv[i]);
    }
    void *test = malloc(100);
    test = realloc(test, 10000);
    memset(test, '\0', 100);
    strcpy(test, "hi");
    printf("test: %s\n", test);
    free(test);

    printf("ceil(1.0) = %d, ceil(1.1) = %d\n", (int)ceil(1.0), (int)ceil(1.1));
    printf("strcmp: %d, %d, %d\n", strcmp("a", "b"), strcmp("b", "a"), strcmp("a", "a"));

    char buf1[6] = {0};
    char buf2[6] = {0};
    FILE *f = fopen("test.file", "w+");
    fwrite("success\n", 1, 8, f);
    fflush(f);
    fseek(f, 0, SEEK_SET);
    fread(buf1, 1, 8, f);
    printf("file test 1: %s\n", buf1);
    fclose(f);

    // freopen?
    f = fopen("test.file", "r");
    fseek(f, 0, SEEK_SET);
    fread(buf2, 1, 8, f);
    printf("file test 2: %s\n", buf2);
    fclose(f);
    return 0;
}
