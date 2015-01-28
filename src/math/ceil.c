#include <stdint.h>

double ceil(double d) {
    return d + (1 - (d - (int64_t)d));
}
