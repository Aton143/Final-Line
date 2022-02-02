#include "Editor.h"
i32 main(i32 ArgCount, i8 **Args) {
  TextWindow Window = {0};
  
  i32 ScreenWidth = 1200;
  i32 ScreenHeight = 900;

  Window.Width = ScreenWidth;
  Window.Height = ScreenHeight;

  InitWindow(ScreenWidth, ScreenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60);

  i32 InputChar = 0;

  i8 TextBufferInformation[100] = {0};
  Font Font = LoadFont("/Users/antoniomartinez/Desktop/Project/TextEditor/Assets/SourceCodePro-Regular.ttf");
  SetTextureFilter(Font.texture, TEXTURE_FILTER_BILINEAR);

  LineBuffer *Lines = CreateLineBuffer(Font, 20, 0);
  
  InitAudioDevice();
  while(!IsAudioDeviceReady()) {;}
  Wave GSound = LoadWave("/Users/antoniomartinez/Desktop/Project/TextEditor/Assets/Guile.wav");
  Sound Song = LoadSoundFromWave(GSound);
  PlaySound(Song);
  Wave Punch = LoadWave("/Users/antoniomartinez/Desktop/Project/TextEditor/Assets/Punch.wav");
  Sound PunchSound = LoadSoundFromWave(Punch);
  
  FileData File = LoadFileIntoLineBuffer(Lines, (u8 *) "/Users/antoniomartinez/Desktop/Project/TextEditor/Source/ex");
  PrintLines(Lines);

  FindShellCommand("build.sh");
  
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    InputChar = GetKeyPressed();
    printf("%d\n", InputChar);
    
    Buffer *TextBuffer = Lines->Lines[Lines->LineIndex];
    
    if ((InputChar >= 39 && InputChar <= 96) || (InputChar == KEY_SPACE)) {
      Insert(TextBuffer, InputChar);
      if (!IsSoundPlaying(PunchSound)) {
	PlaySound(PunchSound);
      }
    }

    if (InputChar == KEY_BACKSPACE) {
      Backspace(Lines);
    }


    // printf("Line Index: %d -- LineLeftIndex: %d -- LineRightIndex: %d\n", Lines->LineIndex, Lines->LeftIndex, Lines->RightIndex);
    if ((InputChar == KEY_RIGHT) || (InputChar == KEY_LEFT)) {
      MoveCursor(Lines, InputChar);
    }
    
    if (InputChar == KEY_UP)/* && Lines->LineIndex == 1*/ {
      MoveCursor(Lines, InputChar);
    }

    if (InputChar == KEY_DOWN)/* && Lines->LineIndex == 0*/ {
      MoveCursor(Lines, InputChar);
    }

    if (InputChar == KEY_TAB) {
      SaveDataIntoFile(Lines, File);
    }

    if (InputChar == KEY_ENTER) {
      Buffer *NewBuffer = CreateBuffer();
      InsertLine(Lines, NewBuffer);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      printf("(%d,%d)\n", GetMouseX(), GetMouseY());
      MoveCursorToMouse(Lines);
    }

    /*
    // i8 *TextToDraw = PrintBuffer(TextBuffer);
    // DrawTextEx(Font, TextToDraw, (Vector2) { (float) 0, (float) -2 }, 20, 0, BLACK);
    // Color FadedViolet = Fade(VIOLET, 0.5f);
    // DrawRectangle(190, 200, 10, 20, FadedViolet);
    
    */
    
    DrawAllLines(Window, Lines);
    DrawCursor(Window, Lines);
    
    snprintf(TextBufferInformation, 100, "Left Index: %d", TextBuffer->LeftIndex);
    Vector2 TextPosition = { (float) 190, (float) 250  };
    DrawTextEx(Font, TextBufferInformation, TextPosition, 20, 0, BLACK);

    snprintf(TextBufferInformation, 100, "Right Index: %d", TextBuffer->RightIndex);
    DrawText(TextBufferInformation, 190, 300, 20, BLACK);
    
    
    //GetInput();
    
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
