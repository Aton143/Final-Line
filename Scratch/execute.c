#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <emmintrin.h>

// int CheckChar(char *Buffer, int Index) {
//   return 
// }

char *GetPath(char *Buffer, int *EndOfPath) {
  int Index;
  for (Index = 0;
       (Index < 255) && Buffer[Index] && !isspace(Buffer[Index]);
       Index++) {}

  char *Path = strndup(Buffer, Index);
  
  while ((Index < 255) && Buffer[Index] && (isspace(Buffer[Index]))) {
    Index++;
  }
  *EndOfPath = Index;

  return Path;
}

char **GetArgs(char *Buffer, int Start, int *ArgCount) {
  int NumOfArgs = 0;
  int Index = Start;
  
  while (Index < 255 && Buffer[Index]) {
    //  printf("Prelim\n");
    while ((Index < 255) && Buffer[Index] && (isspace(Buffer[Index]))) {
      // printf("%c\n", Buffer[Index]);
      Index++;
    }
    // printf("%d\n\n", Index);
    
    if ((Index < 255) && Buffer[Index] && !isspace(Buffer[Index]))
      NumOfArgs++;

    // printf("Nospace\n");
    while ((Index < 255) && Buffer[Index] && (!isspace(Buffer[Index]))) {
      // printf("%c\n", Buffer[Index]);
      Index++;
    }
    // printf("%d\n\n", Index);
    // printf("Space: %d\n", (int) Buffer[Index]);
    while ((Index < 255) && Buffer[Index] && (isspace(Buffer[Index]))) {
      // printf("%c\n", Buffer[Index]);
      Index++;
    }
    // printf("%d\n\n", Index);
  }

  char **Args = (char **) calloc(NumOfArgs + 1, sizeof(char **));

  Index = Start;
  while ((Index < 255) && Buffer[Index] && (isspace(Buffer[Index]))) {
    Index++;
  }
  
  for (int ArgCounter = 0; ArgCounter < NumOfArgs; ArgCounter++) {
    int CurIndex = Index;
    int WordSize = 0;
    
    while ((CurIndex < 255) && Buffer[CurIndex] && !isspace(Buffer[CurIndex])) {
      CurIndex++;
      WordSize++;
    }

    printf("%d\n", WordSize);
    char *Arg = (char *) calloc(WordSize + 1, sizeof(char));
    int ArgIndex = 0;
    
    while (Index < CurIndex) {
      Arg[ArgIndex] = Buffer[Index];
      Index++;
      ArgIndex++;
    }
    
    while ((Index < 255) && Buffer[Index] && (isspace(Buffer[Index]))) {
      Index++;
    }
    Args[ArgCounter] = Arg;
  }

  *ArgCount = NumOfArgs;
  return Args;
}

char **GetPaths(char *Path, int *PathsNum) {
  int Index = 0;
  int NumOfPaths = 0;

  for (; Path[Index]; Index++) {
    if (Path[Index] == ':')
      NumOfPaths++;
  }

  // printf("%d\n", NumOfPaths);
  
  char **Paths = (char **) calloc(NumOfPaths, sizeof(char **));

  Index = 0;
  int PathsIndex = 0;

  while (PathsIndex < NumOfPaths) {
    int PathLength = 0;

    while (Path[Index + PathLength] && Path[Index + PathLength] != ':') PathLength++;
    printf("Path Length: %d\n", PathLength);
    char *CurrentPath = (char *) calloc(PathLength + 1, sizeof(char));

    PathLength = 0;
    while (Path[Index + PathLength] && Path[Index + PathLength] != ':') {
      CurrentPath[PathLength] = Path[Index + PathLength];
      PathLength++;
    }

    Paths[PathsIndex] = CurrentPath;
    Index += PathLength + 1;
    PathsIndex++;
  }

  *PathsNum = NumOfPaths;
  return Paths;
}

void Execute(char *FilePath, char **Args) {
  int FileDes[2] = {0};
  pid_t PID;

  int PipeError = pipe(FileDes);
  if (PipeError == -1) {
    printf("Failure\n");
  }

  PID = fork();
  if (PID == -1) {
    printf("Failure to make process shine\n");
  }

  if (PID == 0) { // CHILD
    dup2(FileDes[1], STDOUT_FILENO);
    close(FileDes[0]);
    close(FileDes[1]);

    execve(FilePath, Args, NULL);
  } else {
    close(FileDes[1]);
    char Buffer[4096] = {0};
    int nbytes = read(FileDes[0], Buffer, sizeof(Buffer));
    printf("Output: (%.*s)\n", nbytes, Buffer);
    wait(NULL);
  }
}

int main() {
  char Buffer[256] = {0};

  char *PathEnv = getenv("PATH");
  // printf("%s\n", PathEnv);

  int NumPaths = 0;
  char **Paths = GetPaths(PathEnv, &NumPaths);

  for (int i = 0; i < NumPaths; i++) {
    printf("%s\n", Paths[i]);
  }

  printf("Please enter a program you'd like to run: ");
  fgets(Buffer, 255, stdin);
  printf("This is the program: %s\n", Buffer);

  int EndOfPath;
  char *Path = GetPath(Buffer, &EndOfPath);

  printf("Path: %s\nIndex: %d\n", Path, EndOfPath);

  int ArgCount;
  char **Args = GetArgs(Buffer, 0, &ArgCount);

  printf("Number of Arguments: %d\n", ArgCount);
  for (int i = 0; i < ArgCount; i++) {
    printf("%s\n", Args[i]);
  }

  for(int i = 0; i < NumPaths; i++) {
    char Buffer[256] = {0};
    strncat(Buffer, Paths[i], 256);
    strncat(Buffer, "/", 256);
    strncat(Buffer, Args[0], 256);

    printf("%s\n", Buffer);
    char *New = strdup(Buffer);
    // Args[0] = New;
    Execute(New, Args);
  }
  
  
  return 0;
}
