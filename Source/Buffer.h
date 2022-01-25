#ifndef BUFFER_HEADER
#define BUFFER_HEADER
#include "Editor.h"

typedef enum BufferReturn {
  TOO_MANY_LINES,
} BufferError;

typedef struct Buffer {
  i8 Text[128];
  i32 LeftIndex;
  i32 RightIndex;
} Buffer;

typedef struct LineBuffer {
  Buffer **Lines;
  i32 Size;
  i32 LeftIndex;
  i32 RightIndex;
  i32 LineIndex;
} LineBuffer;

#define RANGE_EXCL(X, LEFT, RIGHT) (((X) > (LEFT)) && ((X) < (RIGHT)))
#define BUFFER_LEN 14

void Backspace(Buffer *TextBuffer);
void Insert(Buffer *TextBuffer, i8 CharToAdd);
void MoveCursor(LineBuffer *Lines, i32 Direction);
i8 *PrintBuffer(Buffer *TextBuffer);
void InsertLine(LineBuffer *Lines, Buffer *BufferToAdd);
void RemoveLine(LineBuffer *Lines);
void PrintLines(LineBuffer *Lines);

#endif
