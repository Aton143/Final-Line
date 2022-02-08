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
  Macro *UKM = (Macro *) calloc(NUM_OF_ALPHANUM_KEYS, sizeof(Macro *));
  UKM[0] = (Macro) {KEY_SPACE, Output, ' '};
  UKM[1] = (Macro) {KEY_ENTER, Output, '\n'};      // insert function
  UKM[2] = (Macro) {KEY_TAB, Output, '\t'};        // tab function
  UKM[3] = (Macro) {KEY_DELETE, Output, ' '};      // backspace function
  UKM[4] = (Macro) {KEY_RIGHT, Output, ' '};       // arrow key
  UKM[5] = (Macro) {KEY_LEFT, Output, ' '};        // arrow key
  UKM[6] = (Macro) {KEY_UP, Output, ' '};          // arrow key
  UKM[7] = (Macro) {KEY_DOWN, Output, ' '};        // arrow key
  UKM[8] = (Macro) {KEY_CAPS_LOCK, Output, ' '};   // F key
  UKM[9] = (Macro) {KEY_F1, Output, ' '};          // F key
  UKM[10] = (Macro) {KEY_F2, Output, ' '};         // F key
  UKM[11] = (Macro) {KEY_F3, Output, ' '};         // F key
  UKM[12] = (Macro) {KEY_F4, Output, ' '};         // F key
  UKM[13] = (Macro) {KEY_F5, Output, ' '};         // F key
  UKM[14] = (Macro) {KEY_F6, Output, ' '};         // F key
  UKM[15] = (Macro) {KEY_F7, Output, ' '};         // F key
  UKM[16] = (Macro) {KEY_F8, Output, ' '};         // F key
  UKM[17] = (Macro) {KEY_F9, Output, ' '};         // F key
  UKM[18] = (Macro) {KEY_F10, Output, ' '};        // F key
  UKM[19] = (Macro) {KEY_F11, Output, ' '};        // F key
  UKM[20] = (Macro) {KEY_F12, Output, ' '};        // F key
  UKM[21] = (Macro) {KEY_APOSTROPHE, Output, '\''}; 
  UKM[22] = (Macro) {KEY_COMMA, Output, ','};
  UKM[23] = (Macro) {KEY_MINUS, Output, '-'};
  UKM[24] = (Macro) {KEY_PERIOD, Output, '.'};
  UKM[25] = (Macro) {KEY_SLASH, Output, '/'};
  UKM[26] = (Macro) {KEY_ZERO, Output, '0'};
  UKM[27] = (Macro) {KEY_ONE, Output, '1'};
  UKM[28] = (Macro) {KEY_TWO, Output, '2'};
  UKM[29] = (Macro) {KEY_THREE, Output,'3' };
  UKM[30] = (Macro) {KEY_FOUR, Output, '4'};
  UKM[31] = (Macro) {KEY_FIVE, Output, '5'};
  UKM[32] = (Macro) {KEY_SIX, Output, '6'};
  UKM[33] = (Macro) {KEY_SEVEN, Output, '7'};
  UKM[34] = (Macro) {KEY_EIGHT, Output, '8'};
  UKM[35] = (Macro) {KEY_NINE, Output, '9'};
  UKM[36] = (Macro) {KEY_SEMICOLON, Output, ';'};
  UKM[37] = (Macro) {KEY_EQUAL, Output, '='};
  UKM[38] = (Macro) {KEY_A, Output, 'a'};
  UKM[39] = (Macro) {KEY_B, Output, 'b'};
  UKM[40] = (Macro) {KEY_C, Output, 'c'};
  UKM[41] = (Macro) {KEY_D, Output, 'd'};
  UKM[42] = (Macro) {KEY_E, Output, 'e'};
  UKM[43] = (Macro) {KEY_F, Output, 'f'};
  UKM[44] = (Macro) {KEY_G, Output, 'g'};
  UKM[45] = (Macro) {KEY_H, Output, 'h'};
  UKM[46] = (Macro) {KEY_I, Output, 'i'};
  UKM[47] = (Macro) {KEY_J, Output, 'j'};
  UKM[48] = (Macro) {KEY_K, Output, 'k'};
  UKM[49] = (Macro) {KEY_L, Output, 'l'};
  UKM[50] = (Macro) {KEY_M, Output, 'm'};
  UKM[51] = (Macro) {KEY_N, Output, 'n'};
  UKM[52] = (Macro) {KEY_O, Output, 'o'};
  UKM[53] = (Macro) {KEY_P, Output, 'p'};
  UKM[54] = (Macro) {KEY_Q, Output, 'q'};
  UKM[55] = (Macro) {KEY_R, Output, 'r'};
  UKM[56] = (Macro) {KEY_S, Output, 's'};
  UKM[57] = (Macro) {KEY_T, Output, 't'};
  UKM[58] = (Macro) {KEY_U, Output, 'u'};
  UKM[59] = (Macro) {KEY_V, Output, 'v'};
  UKM[60] = (Macro) {KEY_W, Output, 'w'};
  UKM[61] = (Macro) {KEY_X, Output, 'x'};
  UKM[62] = (Macro) {KEY_Y, Output, 'y'};
  UKM[63] = (Macro) {KEY_Z, Output, 'z'};
  UKM[64] = (Macro) {KEY_LEFT_BRACKET, Output, '['};
  UKM[65] = (Macro) {KEY_RIGHT_BRACKET, Output, ']'};
  UKM[66] = (Macro) {KEY_BACKSLASH, Output, '\\'};
  UKM[67] = (Macro) {KEY_GRAVE, Output, '`'};

  UnmodifiedKeys.Macros = UKM;
  UnmodifiedKeys.LastIndex = 67;
  UnmodifiedKeys.Size = NUM_OF_ALPHANUM_KEYS;
  //******************************************************************
  
  //------------------------------------------------------------------
  MacroList ShiftKeys;
  Macro *SKM = (Macro *) calloc(NUM_OF_ALPHANUM_KEYS, sizeof(Macro *));
  SKM[0] = (Macro) {KEY_APOSTROPHE, Output, '"'}; 
  SKM[1] = (Macro) {KEY_COMMA, Output, '<'};
  SKM[2] = (Macro) {KEY_MINUS, Output, '_'};
  SKM[3] = (Macro) {KEY_PERIOD, Output, '>'};
  SKM[4] = (Macro) {KEY_SLASH, Output, '?'};
  SKM[5] = (Macro) {KEY_ZERO, Output, ')'};
  SKM[6] = (Macro) {KEY_ONE, Output, '!'};
  SKM[7] = (Macro) {KEY_TWO, Output, '@'};
  SKM[8] = (Macro) {KEY_THREE, Output,'#' };
  SKM[9] = (Macro) {KEY_FOUR, Output, '$'};
  SKM[10] = (Macro) {KEY_FIVE, Output, '%'};
  SKM[11] = (Macro) {KEY_SIX, Output, '^'};
  SKM[12] = (Macro) {KEY_SEVEN, Output, '&'};
  SKM[13] = (Macro) {KEY_EIGHT, Output, '*'};
  SKM[14] = (Macro) {KEY_NINE, Output, '('};
  SKM[15] = (Macro) {KEY_SEMICOLON, Output, ':'};
  SKM[16] = (Macro) {KEY_EQUAL, Output, '+'};
  SKM[17] = (Macro) {KEY_A, Output, 'A'};
  SKM[18] = (Macro) {KEY_B, Output, 'B'};
  SKM[19] = (Macro) {KEY_C, Output, 'C'};
  SKM[20] = (Macro) {KEY_D, Output, 'D'};
  SKM[21] = (Macro) {KEY_E, Output, 'E'};
  SKM[22] = (Macro) {KEY_F, Output, 'F'};
  SKM[23] = (Macro) {KEY_G, Output, 'G'};
  SKM[24] = (Macro) {KEY_H, Output, 'H'};
  SKM[25] = (Macro) {KEY_I, Output, 'I'};
  SKM[26] = (Macro) {KEY_J, Output, 'J'};
  SKM[27] = (Macro) {KEY_K, Output, 'K'};
  SKM[28] = (Macro) {KEY_L, Output, 'L'};
  SKM[29] = (Macro) {KEY_M, Output, 'M'};
  SKM[30] = (Macro) {KEY_N, Output, 'N'};
  SKM[31] = (Macro) {KEY_O, Output, 'O'};
  SKM[32] = (Macro) {KEY_P, Output, 'P'};
  SKM[33] = (Macro) {KEY_Q, Output, 'Q'};
  SKM[34] = (Macro) {KEY_R, Output, 'R'};
  SKM[35] = (Macro) {KEY_S, Output, 'S'};
  SKM[36] = (Macro) {KEY_T, Output, 'T'};
  SKM[37] = (Macro) {KEY_U, Output, 'U'};
  SKM[38] = (Macro) {KEY_V, Output, 'V'};
  SKM[39] = (Macro) {KEY_W, Output, 'W'};
  SKM[40] = (Macro) {KEY_X, Output, 'X'};
  SKM[41] = (Macro) {KEY_Y, Output, 'Y'};
  SKM[42] = (Macro) {KEY_Z, Output, 'Z'};
  SKM[43] = (Macro) {KEY_LEFT_BRACKET, Output, '{'};
  SKM[44] = (Macro) {KEY_RIGHT_BRACKET, Output, '}'};
  SKM[45] = (Macro) {KEY_BACKSLASH, Output, '|'};
  SKM[46] = (Macro) {KEY_GRAVE, Output, '~'};

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

u32 MacroSearch(MacroTable Table, KeyboardKey Key, MacroCombo Combo) {
  u32 LastIndex = Table.List[Combo].LastIndex;
  for (u32 MacroIndex = 0; MacroIndex < LastIndex; MacroIndex++) {
    Macro CurrentMacro = Table.List[Combo].Macros[MacroIndex];
    if (CurrentMacro.Key == Key) {
      return MacroIndex;
    }
  }
  return -1;
}

void RegisterMacro(MacroCombo Combo, KeyboardKey Key,
		   MacroType Type, Command Command, MacroTable Table) {
  i32 PossibleMacroIndex = MacroSearch(Table, Key, Combo);

  if (PossibleMacroIndex != -1) {
    Table.List[Combo].Macros[PossibleMacroIndex] = (Macro) {Key, Type, Command};
  } else if (Table.List[Combo].Size == 0) {
      Macro *List = (Macro *) calloc(STARTING_MACRO_SIZE, sizeof(Macro));
      List[0] = (Macro) {Key, Type, Command};
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
    
    Table.List[Combo].Macros[LastIndex] = (Macro) {Key, Type, Command};
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

void ProcessInput(EditorContext Context, MacroTable Table) {
  u32 Input = 0;
  MacroCombo Combo = GetMacroCombo();

  Input = GetKeyPressed();
  printf("Input: %d - Combo: %d\n", Input, Combo);

  if (Input) {
    u32 MacroIndex = MacroSearch(Table, Input, Combo);
    printf("Macro Index: %d\n", MacroIndex);
    if (MacroIndex > -1) {
      Macro CommandMacro = Table.List[Combo].Macros[MacroIndex];
      switch(CommandMacro.Type) {
      case Output: {
	LineBuffer *Lines = Context.CurrentLineBuffer;
	Buffer *Buffer = Lines->Lines[Lines->LineIndex];

	Insert(Buffer, Input);
	break;
      }
      case Function: {
	break;
      }
      default:
	break;
      }
    
    }
  }
}
