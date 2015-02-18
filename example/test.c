#include <unistd.h>
#include "stdlib.h"

int main(int argc, char **argv) {
    printf("hello with printf: %s\n", "world");
    printf("argv:\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    void *test = malloc(100);
    test = realloc(test, 10000);
    memset(test, '\0', 10000);
    strcpy(test, "hi");
    printf("test: %s\n", test);
    free(test);

    char buf1[6] = {0};
    char buf2[6] = {0};
    FILE *f = fopen("test", "w+");
    fwrite("success\n", 1, 8, f);
    fflush(f);
    fseek(f, 0, SEEK_SET);
    fread(buf1, 1, 8, f);
    printf("file test 1: %s\n", buf1);
    fclose(f);

    // freopen?
    f = fopen("test", "r");
    fseek(f, 0, SEEK_SET);
    fread(buf2, 1, 8, f);
    printf("file test 2: %s\n", buf2);
    fclose(f);

    return 0;
}
