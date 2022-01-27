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
  
  return File;
}

