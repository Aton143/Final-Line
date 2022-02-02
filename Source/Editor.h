#ifndef EDITOR_HEADER
#define EDITOR_HEADER
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "raylib.h"

#define ASSERT(Expression) if (!(Expression)) {* (volatile int *) 0 = 0;}
#define DEFAULT_USLEEP_PERIOD     500
#define BUFFER_LEN                128
#define DEFAULT_LINE_BUFFER_SIZE  4096
#define MODIFIER_TYPE_COUNT       16
#define NUM_OF_ALPHANUM_KEYS      64

typedef enum Modifiers {
  SHIFT   =      1,
  CONTROL =      1 << 1,
  ALT     =      1 << 2,
  SUPER   =      1 << 3
} Modifiers;

typedef enum BufferReturn {
  TOO_MANY_LINES,
} BufferError;

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

typedef Vector2  Vec2;
typedef Vector3  Vec3;

typedef struct TextWindow {
  u32            Width;
  u32            Height;
} TextWindow;

typedef struct Buffer {
  i8             Text[BUFFER_LEN];

  u32            LeftIndex;
  u32            RightIndex;
} Buffer;

typedef Buffer CommandBuffer;

typedef struct LineBuffer {
  Buffer       **Lines;
  u32            Size;       // in bytes
  
  u32            LeftIndex;
  u32            RightIndex;
  u32            LineIndex;
  
  Font           Font;
  r32            FontWidth;
  r32            FontHeight;
} LineBuffer;

typedef struct FileData {
  u8            *Data;
  u8            *Name;
  u32            Size;
} FileData;

typedef union Command {
  u32            Output;
  void         (*Function)(LineBuffer *);
} Command;

typedef struct {
  Command CommandMatrix[MODIFIER_TYPE_COUNT][MODIFIER_TYPE_COUNT][NUM_OF_ALPHANUM_KEYS];
} Commands;


#include "Memory.h"
#include "File.h"
#include "Buffer.h"
#include "Render.h"
#endif /* EDITOR_HEADER */
