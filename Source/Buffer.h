#ifndef BUFFER_HEADER
#define BUFFER_HEADER
#include "Editor.h"

#define RANGE_EXCL(X, LEFT, RIGHT) (((X) > (LEFT)) && ((X) < (RIGHT)))
#define BUFFER_LEN 14

void Backspace(Buffer *TextBuffer);
void Insert(Buffer *TextBuffer, i8 CharToAdd);
void MoveCursor(LineBuffer *Lines, i32 Direction);
i8  *PrintBuffer(Buffer *TextBuffer);
void InsertLine(LineBuffer *Lines, Buffer *BufferToAdd);
void RemoveLine(LineBuffer *Lines);
void PrintLines(LineBuffer *Lines);

#endif
