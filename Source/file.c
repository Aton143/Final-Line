#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int ArgCount, char **ArgValues) {
  if (ArgCount != 2) return -1;

  FILE * File = fopen(ArgValues[1], "rw");
  if (!File) return -1;

  int FileDescriptor = fileno(File);
  struct stat FileStatus;
  if (fstat(FileDescriptor, &FileStatus) < 0) return 0;

  printf("File size: %d\n", (int) FileStatus.st_size);
  
  return 0;
}
