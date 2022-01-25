#include "Editor.h"

i8 GetModifiers() {
  i8 ReturnModifiers = 0;
  if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ReturnModifiers |= SHIFT;
  if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) ReturnModifiers |= CONTROL;
  if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) ReturnModifiers |= ALT;
  if (IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER)) ReturnModifiers |= SUPER;

  return ReturnModifiers;
}

i8 ProcessInput() {
  i32 InputChar = 0;
  i8 Modifiers = GetModifiers();
  
  do {
    InputChar = GetCharPressed();
  } while (InputChar);

  return 0;
}

i32 main(i32 ArgCount, i8 **Args) {
  i32 ScreenWidth = 800;
  i32 ScreenHeight = 450;

  InitWindow(ScreenWidth, ScreenHeight, "raylib [core] example - basic window");
  SetTargetFPS(10);

  Buffer *TextBuffer1 = (Buffer *) calloc(1, sizeof(Buffer));
  Buffer *TextBuffer2 = (Buffer *) calloc(1, sizeof(Buffer));
  
  TextBuffer1->RightIndex = 14;
  TextBuffer2->RightIndex = 14;

  LineBuffer *Lines = (LineBuffer *) calloc(1, sizeof(LineBuffer));
  Buffer **LinesForLineBuffer = (Buffer **) calloc(10, sizeof(Buffer **));
  Lines->Lines = LinesForLineBuffer;
  Lines->LineIndex = 0;
  Lines->LeftIndex = 2;
  Lines->RightIndex = 9;
  Lines->Lines[0] = TextBuffer1;
  Lines->Lines[1] = TextBuffer2;
  Lines->Size = 10;
  
  i32 InputChar = 0;

  i8 TextBufferInformation[100] = {0};
  Font Font = LoadFont("/Users/antoniomartinez/Desktop/Project/TextEditor/Assets/SourceCodePro-Regular.ttf");
  SetTextureFilter(Font.texture, TEXTURE_FILTER_BILINEAR);
  
  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    InputChar = GetKeyPressed();

    Buffer *TextBuffer = Lines->Lines[Lines->LineIndex];
    
    if ((InputChar >= 39 && InputChar <= 96) || (InputChar == KEY_SPACE)) {
      Insert(TextBuffer, InputChar);
    }

    if (InputChar == KEY_BACKSPACE) {
      Backspace(TextBuffer);
    }

    
    if ((InputChar == KEY_RIGHT) || (InputChar == KEY_LEFT)) {
      MoveCursor(Lines, InputChar);
    }
    
    if ((InputChar == KEY_UP) && Lines->LineIndex == 1) {
      MoveCursor(Lines, InputChar);
    }

    if ((InputChar == KEY_DOWN) && Lines->LineIndex == 0) {
      MoveCursor(Lines, InputChar);
    }

    i8 *TextToDraw = PrintBuffer(TextBuffer);
    DrawTextEx(Font, TextToDraw, (Vector2) { (float) 190, (float) 200 }, 20, 0, BLACK);
    Color FadedViolet = Fade(VIOLET, 0.5f);
    DrawRectangle(190, 200, 10, 20, FadedViolet);

    Vector2 TextMeasure = MeasureTextEx(Font, TextToDraw, 20, 0);
    printf("width: %f - height: %f\n", TextMeasure.x, TextMeasure.y);
    
    free(TextToDraw);

    snprintf(TextBufferInformation, 100, "Left Index: %d", TextBuffer->LeftIndex);
    Vector2 TextPosition = { (float) 190, (float) 250  };
    DrawTextEx(Font, TextBufferInformation, TextPosition, 20, 0, BLACK);

    snprintf(TextBufferInformation, 100, "Right Index: %d", TextBuffer->RightIndex);
    DrawText(TextBufferInformation, 190, 300, 20, BLACK);

    //PrintLines(Lines);
    
    //GetInput();
    
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
