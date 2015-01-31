#include "io.h"

int main(int argc, char **argv) {
    printf("hello with printf: %s\n", "world");
    printf("argv:\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
