#include "Input.h"

i8 GetModifiers() {
  i8 ReturnModifiers = 0;
  if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ReturnModifiers |= SHIFT_MOD;
  if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) ReturnModifiers |= CONTROL_MOD;
  if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) ReturnModifiers |= ALT_MOD;
  if (IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER)) ReturnModifiers |= SUPER_MOD;

  return ReturnModifiers;
}

MacroTable CreateMacroTable() {
  //------------------------------------------------------------------
  MacroList UnmodifiedKeys;
  // UKM: unmodified key macros
  Macro *UKM = (Macro *) calloc(NUM_OF_ALPHANUM_KEYS, sizeof(Macro));
  UKM[0] = (Macro) {KEY_SPACE, InsertInput, (void *) ' '};
  UKM[1] = (Macro) {KEY_ENTER, InsertLineInput, NULL};      // insert function
  UKM[2] = (Macro) {KEY_TAB, SaveDataInput, NULL};                   // tab function
  UKM[3] = (Macro) {KEY_BACKSPACE, BackspaceInput, NULL};      // backspace function
  UKM[4] = (Macro) {KEY_RIGHT, MoveCursorInput, (void *) KEY_RIGHT}; // right
  UKM[5] = (Macro) {KEY_LEFT, MoveCursorInput, (void *) KEY_LEFT};   // left
  UKM[6] = (Macro) {KEY_UP, MoveCursorInput, (void *) KEY_UP};       // up
  UKM[7] = (Macro) {KEY_DOWN, MoveCursorInput, (void *) KEY_DOWN};    // down
  UKM[8] = (Macro) {KEY_CAPS_LOCK, NULL, NULL};             // F key
  UKM[9] = (Macro) {KEY_F1, NULL, NULL};                    // F key
  UKM[10] = (Macro) {KEY_F2, NULL, NULL};                   // F key
  UKM[11] = (Macro) {KEY_F3, NULL, NULL};                   // F key
  UKM[12] = (Macro) {KEY_F4, NULL, NULL};                   // F key
  UKM[13] = (Macro) {KEY_F5, NULL, NULL};                   // F key
  UKM[14] = (Macro) {KEY_F6, NULL, NULL};                   // F key
  UKM[15] = (Macro) {KEY_F7, NULL, NULL};                   // F key
  UKM[16] = (Macro) {KEY_F8, NULL, NULL};                   // F key
  UKM[17] = (Macro) {KEY_F9, NULL, NULL};                   // F key
  UKM[18] = (Macro) {KEY_F10, NULL, NULL};                  // F key
  UKM[19] = (Macro) {KEY_F11, NULL, NULL};                  // F key
  UKM[20] = (Macro) {KEY_F12, NULL, NULL};                  // F key
  UKM[21] = (Macro) {KEY_APOSTROPHE, InsertInput, (void *) '\''};
  UKM[22] = (Macro) {KEY_COMMA, InsertInput, (void *) ','};
  UKM[23] = (Macro) {KEY_MINUS, InsertInput, (void *) '-'};
  UKM[24] = (Macro) {KEY_PERIOD, InsertInput, (void *) '.'};
  UKM[25] = (Macro) {KEY_SLASH, InsertInput, (void *) '/'};
  UKM[26] = (Macro) {KEY_ZERO, InsertInput, (void *) '0'};
  UKM[27] = (Macro) {KEY_ONE, InsertInput, (void *) '1'};
  UKM[28] = (Macro) {KEY_TWO, InsertInput, (void *) '2'};
  UKM[29] = (Macro) {KEY_THREE, InsertInput, (void *) '3'};
  UKM[30] = (Macro) {KEY_FOUR, InsertInput, (void *) '4'};
  UKM[31] = (Macro) {KEY_FIVE, InsertInput, (void *) '5'};
  UKM[32] = (Macro) {KEY_SIX, InsertInput, (void *) '6'};
  UKM[33] = (Macro) {KEY_SEVEN, InsertInput, (void *) '7'};
  UKM[34] = (Macro) {KEY_EIGHT, InsertInput, (void *) '8'};
  UKM[35] = (Macro) {KEY_NINE, InsertInput, (void *) '9'};
  UKM[36] = (Macro) {KEY_SEMICOLON, InsertInput, (void *) ';'};
  UKM[37] = (Macro) {KEY_EQUAL, InsertInput, (void *) '='};
  UKM[38] = (Macro) {KEY_A, InsertInput, (void *) 'a'};
  UKM[39] = (Macro) {KEY_B, InsertInput, (void *) 'b'};
  UKM[40] = (Macro) {KEY_C, InsertInput, (void *) 'c'};
  UKM[41] = (Macro) {KEY_D, InsertInput, (void *) 'd'};
  UKM[42] = (Macro) {KEY_E, InsertInput, (void *) 'e'};
  UKM[43] = (Macro) {KEY_F, InsertInput, (void *) 'f'};
  UKM[44] = (Macro) {KEY_G, InsertInput, (void *) 'g'};
  UKM[45] = (Macro) {KEY_H, InsertInput, (void *) 'h'};
  UKM[46] = (Macro) {KEY_I, InsertInput, (void *) 'i'};
  UKM[47] = (Macro) {KEY_J, InsertInput, (void *) 'j'};
  UKM[48] = (Macro) {KEY_K, InsertInput, (void *) 'k'};
  UKM[49] = (Macro) {KEY_L, InsertInput, (void *) 'l'};
  UKM[50] = (Macro) {KEY_M, InsertInput, (void *) 'm'};
  UKM[51] = (Macro) {KEY_N, InsertInput, (void *) 'n'};
  UKM[52] = (Macro) {KEY_O, InsertInput, (void *) 'o'};
  UKM[53] = (Macro) {KEY_P, InsertInput, (void *) 'p'};
  UKM[54] = (Macro) {KEY_Q, InsertInput, (void *) 'q'};
  UKM[55] = (Macro) {KEY_R, InsertInput, (void *) 'r'};
  UKM[56] = (Macro) {KEY_S, InsertInput, (void *) 's'};
  UKM[57] = (Macro) {KEY_T, InsertInput, (void *) 't'};
  UKM[58] = (Macro) {KEY_U, InsertInput, (void *) 'u'};
  UKM[59] = (Macro) {KEY_V, InsertInput, (void *) 'v'};
  UKM[60] = (Macro) {KEY_W, InsertInput, (void *) 'w'};
  UKM[61] = (Macro) {KEY_X, InsertInput, (void *) 'x'};
  UKM[62] = (Macro) {KEY_Y, InsertInput, (void *) 'y'};
  UKM[63] = (Macro) {KEY_Z, InsertInput, (void *) 'z'};
  UKM[64] = (Macro) {KEY_LEFT_BRACKET, InsertInput, (void *) '['};
  UKM[65] = (Macro) {KEY_RIGHT_BRACKET, InsertInput, (void *) ']'};
  UKM[66] = (Macro) {KEY_BACKSLASH, InsertInput, (void *) '\\'};
  UKM[67] = (Macro) {KEY_GRAVE, InsertInput, (void *) '`'};

  UnmodifiedKeys.Macros = UKM;
  UnmodifiedKeys.LastIndex = 68;
  UnmodifiedKeys.Size = NUM_OF_ALPHANUM_KEYS;
  //******************************************************************
  
  //------------------------------------------------------------------
  MacroList ShiftKeys;
  Macro *SKM = (Macro *) calloc(NUM_OF_ALPHANUM_KEYS, sizeof(Macro));
  SKM[0] = (Macro) {KEY_APOSTROPHE, InsertInput, (void *) '"'}; 
  SKM[1] = (Macro) {KEY_COMMA, InsertInput, (void *) '<'};
  SKM[2] = (Macro) {KEY_MINUS, InsertInput, (void *) '_'};
  SKM[3] = (Macro) {KEY_PERIOD, InsertInput, (void *) '>'};
  SKM[4] = (Macro) {KEY_SLASH, InsertInput, (void *) '?'};
  SKM[5] = (Macro) {KEY_ZERO, InsertInput, (void *) ')'};
  SKM[6] = (Macro) {KEY_ONE, InsertInput, (void *) '!'};
  SKM[7] = (Macro) {KEY_TWO, InsertInput, (void *) '@'};
  SKM[8] = (Macro) {KEY_THREE, InsertInput, (void *) '#'};
  SKM[9] = (Macro) {KEY_FOUR, InsertInput, (void *) '$'};
  SKM[10] = (Macro) {KEY_FIVE, InsertInput, (void *) '%'};
  SKM[11] = (Macro) {KEY_SIX, InsertInput, (void *) '^'};
  SKM[12] = (Macro) {KEY_SEVEN, InsertInput, (void *) '&'};
  SKM[13] = (Macro) {KEY_EIGHT, InsertInput, (void *) '*'};
  SKM[14] = (Macro) {KEY_NINE, InsertInput, (void *) '('};
  SKM[15] = (Macro) {KEY_SEMICOLON, InsertInput, (void *) ':'};
  SKM[16] = (Macro) {KEY_EQUAL, InsertInput, (void *) '+'};
  SKM[17] = (Macro) {KEY_A, InsertInput, (void *) 'A'};
  SKM[18] = (Macro) {KEY_B, InsertInput, (void *) 'B'};
  SKM[19] = (Macro) {KEY_C, InsertInput, (void *) 'C'};
  SKM[20] = (Macro) {KEY_D, InsertInput, (void *) 'D'};
  SKM[21] = (Macro) {KEY_E, InsertInput, (void *) 'E'};
  SKM[22] = (Macro) {KEY_F, InsertInput, (void *) 'F'};
  SKM[23] = (Macro) {KEY_G, InsertInput, (void *) 'G'};
  SKM[24] = (Macro) {KEY_H, InsertInput, (void *) 'H'};
  SKM[25] = (Macro) {KEY_I, InsertInput, (void *) 'I'};
  SKM[26] = (Macro) {KEY_J, InsertInput, (void *) 'J'};
  SKM[27] = (Macro) {KEY_K, InsertInput, (void *) 'K'};
  SKM[28] = (Macro) {KEY_L, InsertInput, (void *) 'L'};
  SKM[29] = (Macro) {KEY_M, InsertInput, (void *) 'M'};
  SKM[30] = (Macro) {KEY_N, InsertInput, (void *) 'N'};
  SKM[31] = (Macro) {KEY_O, InsertInput, (void *) 'O'};
  SKM[32] = (Macro) {KEY_P, InsertInput, (void *) 'P'};
  SKM[33] = (Macro) {KEY_Q, InsertInput, (void *) 'Q'};
  SKM[34] = (Macro) {KEY_R, InsertInput, (void *) 'R'};
  SKM[35] = (Macro) {KEY_S, InsertInput, (void *) 'S'};
  SKM[36] = (Macro) {KEY_T, InsertInput, (void *) 'T'};
  SKM[37] = (Macro) {KEY_U, InsertInput, (void *) 'U'};
  SKM[38] = (Macro) {KEY_V, InsertInput, (void *) 'V'};
  SKM[39] = (Macro) {KEY_W, InsertInput, (void *) 'W'};
  SKM[40] = (Macro) {KEY_X, InsertInput, (void *) 'X'};
  SKM[41] = (Macro) {KEY_Y, InsertInput, (void *) 'Y'};
  SKM[42] = (Macro) {KEY_Z, InsertInput, (void *) 'Z'};
  SKM[43] = (Macro) {KEY_LEFT_BRACKET, InsertInput, (void *) '{'};
  SKM[44] = (Macro) {KEY_RIGHT_BRACKET, InsertInput, (void *) '}'};
  SKM[45] = (Macro) {KEY_BACKSLASH, InsertInput, (void *) '|'};
  SKM[46] = (Macro) {KEY_GRAVE, InsertInput, (void *) '~'};
  ShiftKeys.Macros = SKM;
  ShiftKeys.LastIndex = 47;
  ShiftKeys.Size = NUM_OF_ALPHANUM_KEYS;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList ControlKeys;
  ControlKeys.Macros = NULL;
  ControlKeys.LastIndex = 0;
  ControlKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList AltKeys;
  AltKeys.Macros = NULL;
  AltKeys.LastIndex = 0;
  AltKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList SuperKeys;
  SuperKeys.Macros = NULL;
  SuperKeys.LastIndex = 0;
  SuperKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList ShiftControlKeys;
  ShiftControlKeys.Macros = NULL;
  ShiftControlKeys.LastIndex = 0;
  ShiftControlKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList ShiftAltKeys;
  ShiftAltKeys.Macros = NULL;
  ShiftAltKeys.LastIndex = 0;
  ShiftAltKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList ShiftSuperKeys;
  ShiftSuperKeys.Macros = NULL;
  ShiftSuperKeys.LastIndex = 0;
  ShiftSuperKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList ControlAltKeys;
  ControlAltKeys.Macros = NULL;
  ControlAltKeys.LastIndex = 0;
  ControlAltKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList ControlSuperKeys;
  ControlSuperKeys.Macros = NULL;
  ControlSuperKeys.LastIndex = 0;
  ControlSuperKeys.Size = 0;
  //******************************************************************

  //------------------------------------------------------------------
  MacroList AltSuperKeys;
  AltSuperKeys.Macros = NULL;
  AltSuperKeys.LastIndex = 0;
  AltSuperKeys.Size = 0;
  //******************************************************************
  
  MacroTable ResultTable = {};
  ResultTable.List[NONE] = UnmodifiedKeys;
  ResultTable.List[SHIFT] = ShiftKeys;
  ResultTable.List[CONTROL] = ControlKeys;
  ResultTable.List[ALT] = AltKeys;
  ResultTable.List[SUPER] = SuperKeys;
  ResultTable.List[SHIFT_CONTROL] = ShiftControlKeys;
  ResultTable.List[SHIFT_ALT] = ShiftAltKeys;
  ResultTable.List[SHIFT_SUPER] = ShiftSuperKeys;
  ResultTable.List[CONTROL_ALT] = ControlAltKeys;
  ResultTable.List[CONTROL_SUPER] = ControlSuperKeys;
  ResultTable.List[ALT_SUPER] = AltSuperKeys;
  
  return ResultTable;
}

i32 MacroSearch(MacroTable Table, KeyboardKey Key, MacroCombo Combo) {
  i32 LastIndex = Table.List[Combo].LastIndex;

  //  printf("Searching for key: %d\n", Key);
  
  for (i32 MacroIndex = 0; MacroIndex < LastIndex; MacroIndex++) {
    Macro CurrentMacro = Table.List[Combo].Macros[MacroIndex];
    //printf("Macro Information - Key: %d - Type: %d - Output: %c\n",
    //   CurrentMacro.Key, CurrentMacro.Type, CurrentMacro.Output.Output);
    if (CurrentMacro.Key == Key) {
      //printf("Found index: %d\n", MacroIndex);
      return MacroIndex;
    }
  }
  return -1;
}

void RegisterMacro(MacroCombo Combo, KeyboardKey Key, InputFunction Function,
		   void *Parameter, MacroTable Table) {
  i32 PossibleMacroIndex = MacroSearch(Table, Key, Combo);

  if (PossibleMacroIndex != -1) {
    Table.List[Combo].Macros[PossibleMacroIndex] = (Macro) {Key, Function, Parameter};
  } else if (Table.List[Combo].Size == 0) {
      Macro *List = (Macro *) calloc(STARTING_MACRO_SIZE, sizeof(Macro));
      List[0] = (Macro) {Key, Function, Parameter};
      Table.List[Combo].Size = STARTING_MACRO_SIZE;
      Table.List[Combo].Macros = List;
      Table.List[Combo].LastIndex = 1;
  } else {
    u32 LastIndex = Table.List[Combo].LastIndex;
    
    if (Table.List[Combo].Size <= LastIndex) {
      u32 NewSize = Table.List[Combo].Size * 2;
      Macro *NewList = (Macro *) realloc(Table.List[Combo].Macros, NewSize);
      Table.List[Combo].Macros = NewList;
      Table.List[Combo].Size = NewSize;
    }
    
    Table.List[Combo].Macros[LastIndex] = (Macro) {Key, Function, Parameter};
  }
}


/*
void ProcessInput(EditorContext Context) {
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
*/

MacroCombo GetMacroCombo() {
  i8 Modifiers = GetModifiers();
  i32 BitsSet = __builtin_popcount((u32) Modifiers);
  if (BitsSet > 2) {
    return NONE;
  }

  i8 ShiftMod = Modifiers & SHIFT_MOD;
  i8 ControlMod = Modifiers & CONTROL_MOD;
  i8 AltMod = Modifiers & ALT_MOD;
  i8 SuperMod = Modifiers & SUPER_MOD;
  
  if (ShiftMod) {
    if (ControlMod) {
      return SHIFT_CONTROL;
    } else if (AltMod) {
      return SHIFT_ALT;
    } else if (SuperMod) {
      return SHIFT_SUPER;
    } else {
      return SHIFT;
    }
  } else if (ControlMod) {
    if (AltMod) {
      return CONTROL_ALT;
    } else if (SuperMod) {
      return CONTROL_SUPER;
    } else {
      return CONTROL;
    }
  } else if (AltMod) {
    if (SuperMod) {
      return ALT_SUPER;
    } else {
      return ALT;
    }
  } else if (SuperMod) {
    return SUPER;
  } else {
    return NONE;
  }
}

void RunCommand(EditorContext Context, MacroTable Table,
		KeyboardKey Input, MacroCombo Combo) {
  i32 MacroIndex = MacroSearch(Table, Input, Combo);
  if (MacroIndex > -1) {
    Macro CommandMacro = Table.List[Combo].Macros[MacroIndex];
    if (CommandMacro.Function) {
      CommandMacro.Function(Context, CommandMacro.Parameter);
    }
  }
}

void ProcessInput(EditorContext *Context, MacroTable Table) {
  KeyboardKey Input = 0;
  KeyboardKey LastInput = 0;
  MacroCombo Combo = GetMacroCombo();

  b32 LastKeyDownCheck = IsKeyDown(Context->LastKey);
  printf("Last Key: %c (Check: %s)\n", Context->LastKey, LastKeyDownCheck ? "Same as last" : "Not the same");
  Input = LastKeyDownCheck ? Context->LastKey : GetKeyPressed();
  
  //printf("Input: %d - Combo: %d\n", Input, Combo);
  
  while (Input) {
    RunCommand(*Context, Table, Input, Combo);
    
    LastInput = Input;
    Input = GetKeyPressed();
  }

  printf("Last Input: %c\n", LastInput);
  
  if (!LastKeyDownCheck) {
    Context->LastKey = LastInput;
  }

  printf("Context Last Key: %c\n", Context->LastKey);
}
