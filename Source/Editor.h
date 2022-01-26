#ifndef EDITOR_HEADER
#define EDITOR_HEADER
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include "raylib.h"

#define ASSERT(Expression) if (!(Expression)) {* (volatile int *) 0 = 0;}

typedef enum Modifiers {
  SHIFT =        1,
  CONTROL =      1 << 1,
  ALT =          1 << 2,
  SUPER =        1 << 3
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

typedef enum BufferReturn {
  TOO_MANY_LINES,
} BufferError;

typedef struct TextWindow {
  i32            Width;
  i32            Height;
} TextWindow;

typedef struct Buffer {
  i8             Text[128];
  i32            LeftIndex;
  i32            RightIndex;
} Buffer;

typedef struct LineBuffer {
  Buffer       **Lines;
  i32            Size;
  i32            LeftIndex;
  i32            RightIndex;
  i32            LineIndex;
  Font           Font;
  i32            FontWidth;
  i32            FontHeight;
} LineBuffer;


#include "Buffer.h"
#include "Render.h"
#endif /* EDITOR_HEADER */
