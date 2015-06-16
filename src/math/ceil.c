#include <stdint.h>

double ceil(double d) {
    double frac = d - (int64_t)d;
    return frac ? d + (1 - frac) : d;
}
