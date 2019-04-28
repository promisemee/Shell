#include <dirent.h>

#include "shell.h"
#include "builtin.h"

int size_built = 6;
// int size_built = sizeof(built)/sizeof(struct command);

struct command built[] =
{
  {"hi", "hi : Print \"Hi!\"", shell_hi},
  {"cd", "cd [DIR] : Change the directory to [DIR]", shell_cd},
  {"help", "help : Display information about this shell ", shell_help},
  {"builtin", "builtin : Display list of builtin functions", shell_builtin},
  {"history", "history [-c] : Display history list", shell_history},
  {"exit", "exit : Exit the shell", shell_exit}
};

void shell_exit(int argc, char* argv[]){
  exit(0);
  return;
}

void shell_hi(int argc, char* argv[]){
  printf("\nHi! _(≥∇ ≤)ノミ☆ \n\n");
  return;
}

void shell_cd(int argc, char * argv[]){
  char path[BUFSIZE];
  if (argc<2){
    printf("Wrong Usage : cd [dir]\n");
    return;
  }
  if (strcmp(argv[1], "~")==0){   //move to /home/(username)
    char *buf = getlogin();
    char cd[BUFSIZE] = "/home/";
    strcat(cd, buf);
    chdir(cd);
  }
  else if (chdir(argv[1])==-1){
    printf("No such directory : %s\n", argv[1]);
    return;
  }
  printf("%s\n", getcwd(path, sizeof(path)));
  return;
}

void shell_history(int argc, char * argv[]){
  int k = 0;
  int j = 1;
  if (argc>1){    //has argument
    if (strcmp(argv[1], "-c")==0){   //clear history
      i = 0;
      for(int p = 0; p<=i;p++){
        strcpy(history[p], "\0");
      }
    }
    return;
  }

  while(k<i){
    if (strcmp(history[k], "\0")==0) k++;   //pass empty line
    else{
      printf("  %d    %s\n", j, history[k]);
      j++;
    }
    k++;
  }
}

void shell_help(int argc, char *argv[]){
  // printf(ANSI_COLOR_YELLOW);
  printf("\n**If you're finding a list of builtin functions, type 'builtin'**\n\n");
  printf("Shell built by Kim Dain, 2019\n\n");
  printf("This shell can do :\n");
  printf("\t* execute commands with execvp()\n");
  printf("\t* execute commands with builtin functions\n");
  printf("\t* Multiple pipelines ('|')\n");
  printf("\t* Redirection ('<', '>')\n");
  printf("\n");
  printf("Checkout my git repo -> https://github.com/promisemee/Shell\n\n");
  // printf(ANSI_COLOR_RESET);

  printf("\n");


}

void shell_builtin(int argc, char * argv[]){
  int k = size_built;
  printf("\n* List of Shell Builtin Functions\n\n");
  int i = 0;
  for(int i=0;i<k;i++){
    printf(" %s\n", built[i].builtin);
  }
  printf("\n");
  return;
}
