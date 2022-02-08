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

void SaveDataInput(EditorContext Context, void *Parameter) {
  LineBuffer *Lines = Context.CurrentLineBuffer;
  FileData File = *Lines->File;
  SaveDataIntoFile(Lines, File);
}

void FindShellCommand(i8 *CommandName) {
  // want this to be system independent
  i8 *PathEnv = getenv("PATH");
  printf("String Size: %llu\n", GetStringSize(PathEnv));
  i32 PathEnvIndex = 0;
  b32 Found = false;
 
  while (PathEnv[PathEnvIndex]) {
    printf("Index: %d\n", PathEnvIndex);
    i8 CharToEvaluate = PathEnv[PathEnvIndex];
    
    i8 FindName[128] = {0};
    i32 NameIndex = 0;
    
    while(CharToEvaluate && (CharToEvaluate != ':')) {
      FindName[NameIndex] = CharToEvaluate;
      
      PathEnvIndex++;
      NameIndex++;
      CharToEvaluate = PathEnv[PathEnvIndex];
    }

    FindName[NameIndex] = '/';
    NameIndex++;
    
    for (i32 CommandIndex = 0;
	 CommandName[CommandIndex];
	 CommandIndex++) {
      FindName[NameIndex] = CommandName[CommandIndex];
      NameIndex++;
    }

    // found the file
    if (FileExists(FindName)) {
      Found = true;
    }
    
    if (PathEnv[PathEnvIndex]) {
      PathEnvIndex++;
    }
  }

  i8 *PWD = (i8 *) GetWorkingDirectory();
  i8 FindName[128] = {0};
  i32 NameIndex = 0;
  
  for (;
       PWD[NameIndex];
       NameIndex++) {
    FindName[NameIndex] = PWD[NameIndex];
    }

  FindName[NameIndex] = '/';
  NameIndex++;
  FindName[NameIndex] = 'S';
  NameIndex++;
  FindName[NameIndex] = 'o';
  NameIndex++;
  FindName[NameIndex] = 'u';
  NameIndex++;
  FindName[NameIndex] = 'r';
  NameIndex++;
  FindName[NameIndex] = 'c';
  NameIndex++;
  FindName[NameIndex] = 'e';
  NameIndex++;
  FindName[NameIndex] = '/';
  NameIndex++;

  for (i32 CommandIndex = 0;
       CommandName[CommandIndex];
       CommandIndex++) {
    FindName[NameIndex] = CommandName[CommandIndex];
    NameIndex++;
  }

  printf("Find name: %s\n", FindName);
  
  if (FileExists(FindName)) {
      Found = true;
  }

  printf("Command was %s\n", Found ? "found" : "not found");
}

/*
void FindShellCommandSIMD(i8 *CommandName) {
  i8 *PathEnv = getenv("PATH");
  u64 PathSize = GetStringSize(PathEnv);
  b32 Found = false;
  
  u32 PathIndex = 0;
  u32 FullPathIndex = 0;

  while (PathIndex < PathSize) {
    i8 FullPath[128] = {0};

    __m128i LoadedString =_mm_loadu_si128((__m128 *) String[PathIndex]);
    __m128i ColonMask = _mm_set1_epi8(':');
    __m128i StringWithMask = _mm_cmpeq_epi8(LoadedString, ColonMask);
    __m128i Zero = _mm_set1_epi8(0);
    
    // while no colon is present
    while (!_mm_test_all_zeros(StringWithMask, ColonMask) &&
	   !_mm_test_all_zeros(StringWithMask, ZeroMask)) {
      
      PathIndex += 16;
    }
  }
  
  return;
}
*/
