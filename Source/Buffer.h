#ifndef BUFFER_HEADER
#define BUFFER_HEADER
#include "Editor.h"

#define RANGE_EXCL(X, LEFT, RIGHT) (((X) > (LEFT)) && ((X) < (RIGHT)))

Buffer *CreateBuffer();
LineBuffer *CreateLineBuffer(Font Font, u32 FontSize, u32 Size);
void Backspace(LineBuffer *Lines);
void Insert(Buffer *Buffer, i8 CharToAdd);
void MoveCursor(LineBuffer *Lines, i32 Direction);
i8  *PrintBuffer(Buffer *TextBuffer);
void InsertLine(LineBuffer *Lines, Buffer *BufferToAdd);
void RemoveLine(LineBuffer *Lines);
void PrintLines(LineBuffer *Lines);
void LoadFileIntoLineBuffer(LineBuffer *Lines, u8 *FileName);

#endif
