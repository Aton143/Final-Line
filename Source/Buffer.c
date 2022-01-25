#include "Buffer.h"

void Backspace(Buffer *TextBuffer) {
  if (TextBuffer->LeftIndex > 0) {
    TextBuffer->LeftIndex--;
    TextBuffer->Text[TextBuffer->LeftIndex] = '\0';
  }
}

void Insert(Buffer *TextBuffer, i8 CharToAdd) {
  if (!TextBuffer->Text[TextBuffer->LeftIndex] &&
      (TextBuffer->LeftIndex != TextBuffer->RightIndex)) {
    TextBuffer->Text[TextBuffer->LeftIndex] = CharToAdd;
    TextBuffer->LeftIndex++;
  }
}

void MoveCursorLR(Buffer *TextBuffer, i32 Delta) {
  ASSERT(Delta != 0);
  i32 LeftIndex = TextBuffer->LeftIndex;
  i32 RightIndex = TextBuffer->RightIndex;

  if ((LeftIndex + Delta < 0) || (RightIndex + Delta >= 14)) {
    return;
  }

  if (Delta < 0) {
    for (i32 LeftCounter = 0; LeftCounter > Delta; LeftCounter--) {
      TextBuffer->Text[RightIndex] = TextBuffer->Text[LeftIndex - 1];
      TextBuffer->Text[LeftIndex - 1] = '\0';
      LeftIndex--;
      RightIndex--;
    }
  } else {
    for (i32 RightCounter = 0; RightCounter < Delta; RightCounter++) {
      TextBuffer->Text[LeftIndex] = TextBuffer->Text[RightIndex + 1];
      TextBuffer->Text[RightIndex + 1] = '\0';
      LeftIndex++;
      RightIndex++;
    }
  }

  TextBuffer->LeftIndex = LeftIndex;
  TextBuffer->RightIndex = RightIndex;
}

void MoveCursor(LineBuffer *Lines, i32 Direction) {
  i32 LineIndex = Lines->LineIndex;
  i32 LeftLineIndex = Lines->LeftIndex;
  i32 RightLineIndex = Lines->RightIndex;
  Buffer *CurrentBuffer = Lines->Lines[LineIndex];
  i32 Size = Lines->Size;

  i32 LeftBufferIndex = CurrentBuffer->LeftIndex;
  i32 RightBufferIndex = CurrentBuffer->RightIndex;
    
  if (Direction == KEY_UP && RANGE_EXCL(LeftLineIndex, 0, Size)) {
    Lines->Lines[RightLineIndex] = Lines->Lines[LeftLineIndex - 1];
    Lines->Lines[LeftLineIndex - 1] = NULL;
    LeftLineIndex--;
    RightLineIndex--;

    LineIndex--;

    // Buffer Indices
    Buffer *OldBuffer = CurrentBuffer;
    i32 OldLeftBufferIndex = LeftBufferIndex;
    i32 OldRightBufferIndex = RightBufferIndex;

    Buffer *NewBuffer = Lines->Lines[LineIndex];
    i32 NewLeftBufferIndex = NewBuffer->LeftIndex;
    i32 NewRightBufferIndex = NewBuffer->RightIndex;
    i32 DistanceBetweenIndices = NewRightBufferIndex - NewLeftBufferIndex;
    
    NewLeftBufferIndex = OldLeftBufferIndex;
    NewRightBufferIndex = NewLeftBufferIndex + DistanceBetweenIndices;
    
  }

  if (Direction == KEY_DOWN && RANGE_EXCL(RightLineIndex, 0, Size)) {
    Lines->Lines[LeftLineIndex] = Lines->Lines[RightLineIndex + 1];
    Lines->Lines[RightLineIndex + 1] = NULL;
    LeftLineIndex++;
    RightLineIndex++;

    LineIndex++;
  }

  Lines->LeftIndex = LeftLineIndex;
  Lines->RightIndex = RightLineIndex;
  Lines->LineIndex = LineIndex;

  if (LeftBufferIndex > RightBufferIndex) return;

  if ((Direction == KEY_LEFT) && RANGE_EXCL(LeftBufferIndex, 0, 14)) {
    MoveCursorLR(CurrentBuffer, -1);
  } else if ((Direction == KEY_RIGHT) && RANGE_EXCL(RightBufferIndex, 0, 14)) {
    MoveCursorLR(CurrentBuffer, 1);
  }
}

/*void MoveCursor(Buffer *TextBuffer, i32 Direction) {
  
  

  
  if (TextBuffer->LeftIndex > TextBuffer->RightIndex) {
    return;
  }
  
  
  }*/

i8 *PrintBuffer(Buffer *TextBuffer) {
  i8 *ToPrint = calloc(16, sizeof(i8));
  i32 WriteIndex = 0;
  ToPrint[15] = '\0';
  for (u32 Index = 0; Index < 15; Index++) {
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

    // Need to have a system for what happens to lines in memory
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
