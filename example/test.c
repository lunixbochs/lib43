#include "stdlib.h"

int main(int argc, char **argv) {
    printf("hello with printf: %s\n", "world");
    printf("argv:\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    void *test = malloc(8);
    memset(test, '\0', 8);
    strcpy(test, "hi");
    printf("test: %s\n", test);
    free(test);
    return 0;
}
