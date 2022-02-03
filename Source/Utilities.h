#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER
#include "Editor.h"
#include "cpuid.h"

#define SIMD_ZERO (_mm_set_epi64 ((__m64) {0}, (__m64) {0}))

u64 GetStringSize(i8 *String);

#endif
