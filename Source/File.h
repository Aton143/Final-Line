#ifndef FILE_HEADER
#define FILE_HEADER
#include "Editor.h"

typedef struct SaveData {
  u8 *Data;
  u32 Size;
} SaveData;

FileData OpenFileToMemory(u8 *FileName);
void SaveDataIntoFile(LineBuffer *Lines, FileData File);

#endif
