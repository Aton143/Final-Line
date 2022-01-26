#include "Render.h"

void DrawAllLines(TextWindow Window, LineBuffer *Lines) {
  // Render from the the top
  i32 LeftCounter = 0;
  i32 LeftStoppingPoint = Lines->LeftIndex;
  i32 RightCounter = Lines->RightIndex;
  i32 RightStoppingPoint = Lines->Size;

  i8* LineToPrint = NULL;

  i32 CurrentHeight = 0;

  Font Font = Lines->Font;
  i32 FontHeight = Lines->FontHeight;
  i32 FontWidth = Lines->FontWidth;

  Vector2 LinePosition = {0};
  
  for (; LeftCounter < LeftStoppingPoint; LeftCounter++) {
    Buffer *GetBuffer = Lines->Lines[LeftCounter];
    if (GetBuffer) {
      LineToPrint = PrintBuffer(GetBuffer); 
      DrawTextEx(Font, LineToPrint, LinePosition, FontHeight, 0, BLACK);
      free(LineToPrint);
      LineToPrint = NULL;
      LinePosition.y += FontHeight;
    }
  }

  for (; RightCounter < RightStoppingPoint; RightCounter++) {
    Buffer *GetBuffer = Lines->Lines[RightCounter];
    if (GetBuffer) {
      LineToPrint = PrintBuffer(GetBuffer);
      DrawTextEx(Font, LineToPrint, LinePosition, FontHeight, 0, BLACK);
      free(LineToPrint);
      LineToPrint = NULL;
      LinePosition.y += FontHeight;
    }
  }
}
