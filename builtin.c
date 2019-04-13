#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

int size_built = 2;   //으 전역변수

struct command built[] =
{
  {"cd", shell_cd},
  // {"ls", shell_ls},
  // {"cat", shell_cat},
  // {"chmod", shell_chmod},
  // {"mkdir", shell_mkdir},
  // {"rmdir", shell_rmdir},
  // {"rm", shell_rm},
  {"exit", shell_exit}
};

void shell_cd(int argc, char* argv[]){
  return;
}
// void shell_ls(int argc, char* argv[]){}
// void shell_cat(int argc, char* argv[]){}
// void shell_chmod(int argc, char* argv[]){}
// void shell_mkdir(int argc, char* argv[]){}
// void shell_rmdir(int argc, char* argv[]){}
// void shell_rm(int argc, char* argv[]){}
// void shell_exit(int argc, char* argv[]){}
// void shell_fg(int argc, char* argv[]){}
// void shell_bg(int argc, char* argv[]){}
// void shell_kill(int argc, char* argv[]){}
// void shell_pwd(int argc, char* argv[]){}
// void shell_ps(int argc, char* argv[]){}
// void shell_job(int argc, char* argv[]){}
// void shell_history(int argc, char* argv[]){}
// void shell_clear(int argc, char* argv[]){}
// void shell_help(int argc, char* argv[]){}

void shell_exit(int argc, char* argv[]){
  exit(0);
  return;
}
