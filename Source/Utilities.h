#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER
#include "Editor.h"
#include "cpuid.h"

#define SIMD_ZERO (_mm_set1_epi8(0))

u64 GetStringSize(i8 *String);

#endif
