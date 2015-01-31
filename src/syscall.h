#include <stdint.h>

#ifdef __LP64__
typedef int64_t abi_long;
#else
typedef int32_t abi_long;
#endif

#define sys(name) extern abi_long name();
#include "syscall.list"
#undef sys
