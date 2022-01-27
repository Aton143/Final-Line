#include "Buffer.h"
#include "File.h"

Buffer *CreateBuffer() {
  Buffer *ReturnBuffer = (Buffer *) calloc(1, sizeof(Buffer));
  ReturnBuffer->RightIndex = BUFFER_LEN - 2;
  return ReturnBuffer;
}

// assumes that backspace is valid
void BackspaceInBuffer(Buffer *Buffer) {
  i32 LeftIndex = Buffer->LeftIndex;
  
  LeftIndex--;
  Buffer->Text[LeftIndex] = '\0';

  Buffer->LeftIndex = LeftIndex;
}

void Insert(Buffer *Buffer, i8 CharToAdd) {
  i32 LeftIndex = Buffer->LeftIndex;
  i32 RightIndex = Buffer->RightIndex;
  
  if (!Buffer->Text[LeftIndex] &&
      (LeftIndex != RightIndex)) {
    Buffer->Text[LeftIndex] = CharToAdd;
    LeftIndex++;
    Buffer->LeftIndex = LeftIndex;
  }
}

void MoveCursorLR(Buffer *Buffer, i32 Delta) {
  i32 LeftIndex = Buffer->LeftIndex;
  i32 RightIndex = Buffer->RightIndex;

  if ((LeftIndex + Delta < 0) || (RightIndex + Delta >= BUFFER_LEN - 1)) {
    return;
  }

  if (Delta < 0) {
    for (i32 LeftCounter = 0; LeftCounter > Delta; LeftCounter--) {
      Buffer->Text[RightIndex] = Buffer->Text[LeftIndex - 1];
      Buffer->Text[LeftIndex - 1] = '\0';
      LeftIndex--;
      RightIndex--;
    }
  } else {
    for (i32 RightCounter = 0; RightCounter < Delta; RightCounter++) {
      Buffer->Text[LeftIndex] = Buffer->Text[RightIndex + 1];
      Buffer->Text[RightIndex + 1] = '\0';
      LeftIndex++;
      RightIndex++;
    }
  }

  Buffer->LeftIndex = LeftIndex;
  Buffer->RightIndex = RightIndex;
}

void MoveCursor(LineBuffer *Lines, i32 Direction) {
  i32 LineIndex = Lines->LineIndex;
  i32 LeftLineIndex = Lines->LeftIndex;
  i32 RightLineIndex = Lines->RightIndex;
  Buffer *CurrentBuffer = Lines->Lines[LineIndex];
  i32 Size = Lines->Size;

  i32 LeftBufferIndex = CurrentBuffer->LeftIndex;
  i32 RightBufferIndex = CurrentBuffer->RightIndex;
    
  if (Direction == KEY_UP && RANGE_EXCL(LeftLineIndex, 0, Size + 1)) {
    Lines->Lines[RightLineIndex] = Lines->Lines[LeftLineIndex - 1];
    Lines->Lines[LeftLineIndex - 1] = NULL;
    LeftLineIndex--;
    RightLineIndex--;

    LineIndex--;
  }

  if (Direction == KEY_DOWN && RANGE_EXCL(RightLineIndex, -1, Size)) {
    Lines->Lines[LeftLineIndex] = Lines->Lines[RightLineIndex + 1];
    Lines->Lines[RightLineIndex + 1] = NULL;
    LeftLineIndex++;
    RightLineIndex++;

    LineIndex++;
  }

  
  // Buffer Indices
  i32 OldLeftBufferIndex = LeftBufferIndex;

  Buffer *NewBuffer = Lines->Lines[LineIndex];

  i32 NewLeftBufferIndex = NewBuffer->LeftIndex;
  i32 DistanceBetweenIndices = OldLeftBufferIndex - NewLeftBufferIndex;
    
  MoveCursorLR(NewBuffer, DistanceBetweenIndices);

  Lines->LeftIndex = LeftLineIndex;
  Lines->RightIndex = RightLineIndex;
  Lines->LineIndex = LineIndex;

  ASSERT(LeftBufferIndex <= RightBufferIndex);

  if ((Direction == KEY_LEFT) && RANGE_EXCL(LeftBufferIndex, 0, BUFFER_LEN - 1)) {
    MoveCursorLR(CurrentBuffer, -1);
  } else if ((Direction == KEY_RIGHT) && RANGE_EXCL(RightBufferIndex, -1, BUFFER_LEN - 1)) {
    MoveCursorLR(CurrentBuffer, 1);
  }
}

i8 *PrintBuffer(Buffer *TextBuffer) {
  i8 *ToPrint = calloc(BUFFER_LEN, sizeof(i8));
  i32 WriteIndex = 0;
  ToPrint[15] = '\0';
  for (u32 Index = 0; Index < BUFFER_LEN; Index++) {
    if (TextBuffer->Text[Index]) {
      ToPrint[WriteIndex] = TextBuffer->Text[Index];
      WriteIndex++;
    }
  }
  return ToPrint;
}

void InsertLine(LineBuffer *Lines, Buffer *BufferToAdd) {
  i32 LeftIndex = Lines->LeftIndex;
  i32 RightIndex = Lines->RightIndex;
  
  if (!Lines->Lines[LeftIndex] &&
      (LeftIndex != RightIndex)) {
    Lines->Lines[LeftIndex] = BufferToAdd;
    LeftIndex++;
    Lines->LeftIndex = LeftIndex;
  }
}

void RemoveLine(LineBuffer *Lines) {
  i32 LeftIndex = Lines->LeftIndex;

  if (LeftIndex > 0) {
    LeftIndex--;
    Lines->Lines[LeftIndex] = NULL;

    // need to have a system for what happens to lines in memory
    Lines->LeftIndex = LeftIndex;
  }  
}

void PrintLines(LineBuffer *Lines) {
  i32 LeftCounter = 0;
  i32 LeftStoppingPoint = Lines->LeftIndex;
  i32 RightCounter = Lines->RightIndex;
  i32 RightStoppingPoint = Lines->Size;

  i8* LineToPrint = NULL;

  for (; LeftCounter < LeftStoppingPoint; LeftCounter++) {
    Buffer *GetBuffer = Lines->Lines[LeftCounter];
    if (GetBuffer) {
      LineToPrint = PrintBuffer(GetBuffer);
      printf("%s\n", LineToPrint);
      free(LineToPrint);
      LineToPrint = NULL;
    }
  }

  for (; RightCounter < RightStoppingPoint; RightCounter++) {
    Buffer *GetBuffer = Lines->Lines[RightCounter];
    if (GetBuffer) {
      LineToPrint = PrintBuffer(GetBuffer);
      printf("%s\n", LineToPrint);
      free(LineToPrint);
      LineToPrint = NULL;
    }
  }
}

LineBuffer *CreateLineBuffer(Font Font, u32 FontSize, u32 Size) {
  LineBuffer *ReturnLines = (LineBuffer *) calloc(1, sizeof(LineBuffer));

  if (!Size) Size = DEFAULT_LINE_BUFFER_SIZE;
  Buffer **Lines = (Buffer **) calloc(Size, sizeof(Buffer **));
  ReturnLines->Lines = Lines;
  ReturnLines->Size = Size - 1;
  ReturnLines->LineIndex = 0;
  ReturnLines->LeftIndex = 0;

  ReturnLines->Font = Font;
  Vector2 TextMeasure = MeasureTextEx(Font, "A", FontSize, 0);
  printf("width: %f - height: %f\n", TextMeasure.x, TextMeasure.y);
  ReturnLines->FontWidth = (u32) TextMeasure.x;
  ReturnLines->FontHeight = (u32) TextMeasure.y;

  return ReturnLines;
}

void Backspace(LineBuffer *Lines) {
  i32 LineIndex = Lines->LineIndex;

  Buffer *CurrentBuffer = Lines->Lines[LineIndex];
  i32 BufferLeftIndex = CurrentBuffer->LeftIndex;

  if (BufferLeftIndex > 0) {
    BackspaceInBuffer(CurrentBuffer);
  } else { // delete buffer and update LineIndex
    return;
  }
}

b32 IsNewLine(u8 CheckChar) {
  return (CheckChar == '\n') || (CheckChar == '\r');
}

void LoadFileIntoLineBuffer(LineBuffer *Lines, u8 *FileName) {
  FileData FileData = OpenFileToMemory(FileName);

  u8 *Data = FileData.Data;

  u32 FileIndex = 0;
  u32 FileSize = FileData.Size;
  u32 LineIndex = 0;

  while (FileIndex < FileSize) {
    //printf("Index: %d - FileSize: %d\n", FileIndex, FileSize);
    u32 FileLineIndex = 0;
    
    while (!IsNewLine(Data[FileIndex + FileLineIndex])) FileLineIndex++;

    Lines->Lines[LineIndex] = CreateBuffer();
    Buffer *CurrentBuffer = Lines->Lines[LineIndex];
    for (u32 BufferIndex = 0;
	 BufferIndex < FileLineIndex;
	 BufferIndex++) {
      Insert(CurrentBuffer, Data[FileIndex + BufferIndex]);
      putchar(Data[FileIndex + BufferIndex]);
    }

    putchar('\n');
    ++FileLineIndex;
    FileIndex += FileLineIndex;
    LineIndex++;
    Lines->LeftIndex++;
  }
}
