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
    return 0;
}
