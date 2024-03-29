#ifndef EDITOR_HEADER
#define EDITOR_HEADER
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <immintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include "raylib.h"

#define ASSERT(Expression) if (!(Expression)) {* (volatile int *) 0 = 0;}
#define DEFAULT_USLEEP_PERIOD     500
#define BUFFER_LEN                128
#define DEFAULT_LINE_BUFFER_SIZE  4096
#define MODIFIER_TYPE_COUNT       16
#define NUM_OF_ALPHANUM_KEYS      70
#define MOD_KEY_NUM               4
#define COMBO_NUM                 (1 + MOD_KEY_NUM + ((MOD_KEY_NUM * (MOD_KEY_NUM - 1)) / 2))
#define STARTING_MACRO_SIZE       16
#define TARGET_FPS                60
#define REPEAT_DELAY              TARGET_FPS / 10
#define FIRST_DELAY               TARGET_FPS / 2

typedef enum Modifiers {
  SHIFT_MOD   =      1,
  CONTROL_MOD =      1 << 1,
  ALT_MOD     =      1 << 2,
  SUPER_MOD   =      1 << 3,
} Modifiers;

typedef enum BufferReturn {
  TOO_MANY_LINES,
} BufferError;

typedef enum {
  NONE,
  SHIFT,
  CONTROL,
  ALT,
  SUPER,
  SHIFT_CONTROL,
  SHIFT_ALT,
  SHIFT_SUPER,
  CONTROL_ALT,
  CONTROL_SUPER,
  ALT_SUPER
} MacroCombo;

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
typedef Vec2     V2f;
typedef Vec3     V3f;

typedef struct TextWindow {
  u32            Width;
  u32            Height;
} TextWindow;

typedef TextWindow Window;

typedef struct Buffer {
  i8             Text[BUFFER_LEN];

  u32            LeftIndex;
  u32            RightIndex;
} Buffer;

typedef Buffer CommandBuffer;

typedef struct FileData {
  u8            *Data;
  u8            *Name;
  u32            Size;
} FileData;

typedef struct LineBuffer {
  Buffer       **Lines;
  u32            Size;       // in bytes
  
  u32            LeftIndex;
  u32            RightIndex;
  u32            LineIndex;
  
  Font           Font;
  r32            FontWidth;
  r32            FontHeight;
  
  FileData      *File;
} LineBuffer;

typedef struct {
  LineBuffer   **LineBuffers;
  LineBuffer    *CurrentLineBuffer;
  CommandBuffer *CommandBuffer;
  Window         Window;

  KeyboardKey    LastKey;
  b32            FirstDelay;
  u32            KeyCounter;
} EditorContext;

typedef void (*InputFunction)(EditorContext, void *);

typedef struct {
  KeyboardKey    Key;
  InputFunction  Function;
  void          *Parameter;
} Macro;

typedef struct {
  Macro         *Macros;
  u32            Size;
  u32            LastIndex;
} MacroList;

typedef struct {
  MacroList      List[11];
} MacroTable;

#include "Utilities.h"
#include "Memory.h"
#include "File.h"
#include "Buffer.h"
#include "Render.h"
#include "Input.h"
#endif /* EDITOR_HEADER */
