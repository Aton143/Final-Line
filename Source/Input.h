#ifndef INPUT_HEADER
#define INPUT_HEADER
#include "Editor.h"

#define COMBO_NUM (1 + MOD_KEY_NUM + ((MOD_KEY_NUM * (MOD_KEY_NUM - 1)) / 2))

tyepdef enum {
  NONE,
  SHIFT,
  CONTROL,
  ALT,
  SUPER,
  SHIFT_CONTROL,
  SHIFT_ALT,
  SHIFT_SUPER,
  CONTROL_ALT,
  CONTROL_SUPER,
  ALT_SUPER
} MacroCombo;

typedef enum {
  NoOp,
  Output,
  Function
} MacroType;

typedef struct {
  u32        Key;
  MacroType  Type;
  Command    Output;
} Macro;

typedef struct {
  MacroCombo MacroCombination;
  Macro     *Macros;
  u32        LastIndex;
} MacroList;

typedef struct {
  MacroList *MacroList;
} MacroTable;

#endif
