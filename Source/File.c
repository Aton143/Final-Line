#include "File.h"

FileData OpenFileToMemory(u8 *FileName) {
  if (!FileExists((char *) FileName)) {
    fprintf(stderr, "Open existing file\n");
  }
  
  u32 BytesRead = 0;
  u8 *Data = LoadFileData((char *)FileName, &BytesRead);

  FileData File = {0};
  
  if (!BytesRead || !Data) {
    fprintf(stderr, "Could not open file\n");
    return File;
  }
  File.Data = Data;
  File.Size = BytesRead;
  File.Name = (u8 *) strdup((char *) FileName);
  
  return File;
}

u32 TotalNumberCharacters(LineBuffer *Lines) {
  u32 CharacterCount = 0;
  
  i32 LeftCounter = 0;
  i32 LeftStoppingPoint = Lines->LeftIndex;
  i32 RightCounter = Lines->RightIndex;
  i32 RightStoppingPoint = Lines->Size;
  
  for (; LeftCounter < LeftStoppingPoint; LeftCounter++) {
    Buffer *GetBuffer = Lines->Lines[LeftCounter];
    if (GetBuffer) {
      CharacterCount += NumberCharacters(GetBuffer) + 1;
    }
  }

  for (; RightCounter < RightStoppingPoint; RightCounter++) {
    Buffer *GetBuffer = Lines->Lines[RightCounter];
    if (GetBuffer) {
      CharacterCount += NumberCharacters(GetBuffer) + 1;
    }
  }

  return CharacterCount;
}

void PrintFromIndex(u8 *Data, u32 StartIndex, u32 EndIndex) {
  for (; StartIndex < EndIndex; StartIndex++) {
    // putchar(Data[StartIndex]);
    // printf("Index (%d): %d\n", StartIndex, Data[StartIndex]);
  }
  // putchar('\n');
}

void WriteBufferIntoSaveData(Buffer *Buffer, u8 *SaveData, u32 StartIndex) {
  u32 LeftIndex = Buffer->LeftIndex;
  u32 RightIndex = Buffer->RightIndex;

  // printf("Pre-Start Index: %d ", StartIndex);

  for (u32 Counter = 0;
       Counter < BUFFER_LEN;
       Counter++) {
    u8 Char = Buffer->Text[Counter];
    if (Char) {
      SaveData[StartIndex] = Char;
      StartIndex++;
    }
  }
  
  /*
  for (u32 LeftCounter = 0;
       LeftCounter < LeftIndex;
       LeftCounter++) {
    SaveData[StartIndex] = Buffer->Text[LeftCounter];
    // putchar(Buffer->Text[LeftCounter]);
    StartIndex++;
  }

  for (u32 RightCounter = RightIndex;
       RightCounter < BUFFER_LEN - 1;
       RightCounter++) {
    SaveData[StartIndex] = Buffer->Text[RightCounter];
    // putchar(Buffer->Text[RightCounter]);
    StartIndex++;
  } */

  // printf("Post-Start Index: %d\n", StartIndex);
  
  // putchar('\n');
  SaveData[StartIndex] = '\n';
  // putchar(SaveData[StartIndex]);

}

SaveData SaveDataFromLineBuffer(LineBuffer *Lines) {
  u32 CharacterCount = TotalNumberCharacters(Lines);

  u32 CharacterIndex = 0;
  u8 *Data = (u8 *) calloc(CharacterCount + 1, sizeof(u8));

  i32 LeftCounter = 0;
  i32 LeftStoppingPoint = Lines->LeftIndex;
  i32 RightCounter = Lines->RightIndex;
  i32 RightStoppingPoint = Lines->Size;
  
  for (; LeftCounter < LeftStoppingPoint; LeftCounter++) {
    Buffer *GetBuffer = Lines->Lines[LeftCounter];
    if (GetBuffer) {
      // printf("Character Index: %d\n", CharacterIndex);
      WriteBufferIntoSaveData(GetBuffer, Data, CharacterIndex);
      u32 Delta = NumberCharacters(GetBuffer) + 1;
      // PrintFromIndex(Data, CharacterIndex, CharacterIndex + Delta);
      CharacterIndex += Delta;
    }
  }

  for (; RightCounter < RightStoppingPoint; RightCounter++) {
    Buffer *GetBuffer = Lines->Lines[RightCounter];
    if (GetBuffer) {
      // printf("Character Index: %d\n", CharacterIndex);
      WriteBufferIntoSaveData(GetBuffer, Data, CharacterIndex);
      u32 Delta = NumberCharacters(GetBuffer) + 1;
      // PrintFromIndex(Data, CharacterIndex, CharacterIndex + Delta);
      CharacterIndex += Delta;
    }
  }

  SaveData ReturnSaveData = (SaveData) {Data, CharacterCount};
  PrintFromIndex(Data, 0, CharacterCount);
  printf("%s", Data);
  return ReturnSaveData;
}

void SaveDataIntoFile(LineBuffer *Lines, FileData File) {
  SaveData DataToSave = SaveDataFromLineBuffer(Lines);
  SaveFileData((char *) File.Name, DataToSave.Data, DataToSave.Size);
  free(DataToSave.Data);
}
