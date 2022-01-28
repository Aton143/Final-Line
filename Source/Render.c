#include "Render.h"

void DrawAllLines(TextWindow Window, LineBuffer *Lines) {
  // Render from the the top
  u32 LeftCounter = 0;
  u32 LeftStoppingPoint = Lines->LeftIndex;
  u32 RightCounter = Lines->RightIndex;
  u32 RightStoppingPoint = Lines->Size;

  i8* LineToPrint = NULL;

  u32 CurrentHeight = 0;

  Font Font = Lines->Font;
  u32 FontHeight = Lines->FontHeight;
  u32 FontWidth = Lines->FontWidth;

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

void DrawCursor(TextWindow Window, LineBuffer *Lines) {
  u32 LineIndex = Lines->LineIndex;

  Buffer *Buffer = Lines->Lines[LineIndex];
  u32 LeftIndex = Buffer->LeftIndex;

  // printf("Line index: %d - Left Index: %d\n", LineIndex, LeftIndex);
  
  r32 TopLeftCornerYPos = Lines->FontHeight * LineIndex;
  r32 TopLeftCornerXPos = Lines->FontWidth * LeftIndex;
  Vec2 TopLeftCorner = (Vec2) {TopLeftCornerXPos, TopLeftCornerYPos};

  // printf("(%f, %f)\n", TopLeftCornerXPos, TopLeftCornerYPos);
  
  r32 CursorWidth = ceilf(Lines->FontWidth * (1.10f));
  r32 CursorHeight = ceilf(Lines->FontHeight * (1.10f));
  Vec2 CursorDimensions = (Vec2) {CursorWidth, CursorHeight};

  // printf("Width: %f - Height: %f\n", CursorWidth, CursorHeight);

  Color CursorColor = Fade((Color) VIOLET, 0.5f);

  DrawRectangleV(TopLeftCorner, CursorDimensions, CursorColor);
}
