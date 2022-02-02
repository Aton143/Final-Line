#include "Input.h"
Commands InitializeCommands() {
  Commands ReturnCommands = {0};
  // A-Z
  for (u32 Char = KEY_A;
       Char <= KEY_Z;
       Char++) {
    ReturnCommands.CommandMatrix[0][0][Char].Output = Char;
  }

  return ReturnCommands;
}


i8 GetModifiers() {
  i8 ReturnModifiers = 0;
  if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ReturnModifiers |= SHIFT;
  if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) ReturnModifiers |= CONTROL;
  if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) ReturnModifiers |= ALT;
  if (IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER)) ReturnModifiers |= SUPER;

  return ReturnModifiers;
}

u32 ProcessNumberWithShift(u32 Number) {
  switch(Number) {
  case '1':
    return '!';
  case '2':
    return '@';
  case '3':
    return '#';
  case '4':
    return '$';
  case '5':
    return '%';
  case '6':
    return '^';
  case '7':
    return '&';
  case '8':
    return '*';
  case '9':
    return '(';
  case '0':
    return ')';
  default:
    return '\0';
  }
}

void ProcessInput(LineBuffer *Lines) {
  i32 InputChar = 0;
  i8 Modifiers = GetModifiers();

  u32 LineIndex = Lines->LineIndex;
  Buffer *Buffer = Lines->Lines[LineIndex];

  InputChar = GetCharPressed();
  
  while (InputChar) {
    if ((InputChar >= KEY_A) && (InputChar <= KEY_Z)) { 
      if (Modifiers == SHIFT) {
	Insert(Buffer, InputChar); 
      } else if (!Modifiers) {
	u32 LowercaseDelta = 'A' - 'a';
	Insert(Buffer, InputChar + LowercaseDelta);
      }
    } else if ((InputChar >= KEY_ZERO) && (InputChar <= KEY_NINE)) {
      if (Modifiers == SHIFT) {
	u32 ShiftNumber = ProcessNumberWithShift(InputChar);
	Insert(Buffer, ShiftNumber);
      } else if (!Modifiers) {
	Insert(Buffer, InputChar);
      }
    }
    
    
    InputChar = GetCharPressed();
  }
}

