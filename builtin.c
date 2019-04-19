#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

#define BUFSIZE 2048

int size_built = 3;
//int size_built = sizeof(built)/sizeof(struct command);

struct command built[] =
{
  {"exit", shell_exit},
  {"hi", shell_hi},
  {"cd", shell_cd}
  //{"ls", shell_ls},
  // {"cat", shell_cat},
  // {"chmod", shell_chmod},
  // {"mkdir", shell_mkdir},
  // {"rmdir", shell_rmdir},
  // {"rm", shell_rm}
};

void shell_exit(int argc, char* argv[]){
  exit(0);
  return;
}

void shell_hi(int argc, char* argv[]){
  printf("Hi!\n");
  return;
}

void shell_cd(int argc, char * argv[]){
  if (argc<2){
    printf("Wrong Usage : cd [dir]\n");
    return;
  }
  char path[BUFSIZE];
  if(getcwd(path, sizeof(path))==NULL){
    printf("No such Directory\n");
    exit(0);
  }
  chdir(argv[1]);

  printf("%s\n", path);
  return;
}
