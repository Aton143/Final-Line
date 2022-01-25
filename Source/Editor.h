#ifndef EDITOR_HEADER
#define EDITOR_HEADER
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include "raylib.h"

#define ASSERT(Expression) if (!(Expression)) {* (volatile int *) 0 = 0;}

typedef enum Modifiers {
  SHIFT = 1,
  CONTROL = 1 << 1,
  ALT = 1 << 2,
  SUPER = 1 << 3
} Modifiers;

typedef char     i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef unsigned char uchar;

typedef uchar    u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i32      b32;

typedef float    r32;
typedef double   r64;

#include "Buffer.h"

#endif /* EDITOR_HEADER */