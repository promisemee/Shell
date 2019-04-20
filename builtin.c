#include <dirent.h>

#include "shell.h"
#include "builtin.h"

int size_built = 4;
// int size_built = sizeof(built)/sizeof(struct command);

struct command built[] =
{
  {"hi", "hi : Print \"Hi\"", shell_hi},
  {"cd", "cd [DIR] : Change the directory to DIR", shell_cd},
  {"help", "help : Print list of builtin functions ", shell_help},
  {"exit", "exit : Exit the shell", shell_exit}
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
  if (chdir(argv[1])==-1){
    printf("No such directory : %s\n", argv[1]);
    return;
  }
  printf("%s\n", getcwd(path, sizeof(path)));
  return;
}

void shell_help(int argc, char * argv[]){
  int k = size_built;
  printf("\nList of Shell Builtin Functions\n\n");
  int i = 0;
  for(int i=0;i<k;i++){
    printf(" %s\n", built[i].builtin);
  }
  printf("\n");
  return;
}
