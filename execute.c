#include "shell.h"
#include "builtin.h"
#include "execute.h"

void run_default(char **tokens){
  pid_t pid;
  int status;
  if (tokens[0] == '\0') return;        //blank line
  if (check_builtin(tokens[0]) == 1){   //is builtin function
    command_builtin(tokens);
    return;
  }
  //Not builtin function
  pid = fork();   //fork child process, pid = pid of child process
  if (pid==-1) error("can't fork:");
  if (pid==0){                      //child process
    if (execvp(tokens[0], tokens) == -1){
      printf("No such command : %s\n", tokens[0]);
    }
    exit(0);
  }
  else{         //parent process
    waitpid(pid, &status, 0);
  }

}

void run_pipe(char**left, char** right){
  //for pipe execution
  pid_t pid1, pid2;
  int n, status, fd[2];
  char buff[BUFSIZE];
  if (pipe(fd)<0){
    error("pipe error : ");
  }
  pid1 = fork();
  if(pid1 == -1){
    error("can't fork:");
  }
  if (pid1 == 0){
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    execute_pipe(left);
    exit(0);
  }
  else{
    //parent process
    pid2 = fork();
    if (pid2 == -1){
      error("can't fork:");
    }
    if (pid2 == 0){
      dup2(fd[0], STDIN_FILENO);
      close(fd[1]);
      close(fd[0]);
      execute_pipe(right);
      exit(0);
    }
    else{
      close(fd[0]);
      close(fd[1]);
      waitpid(pid1, &status, 0);
      waitpid(pid2, &status, 0);
    }
  }
}

void execute_pipe(char**token){
  if (check_builtin(token[0])==1){      //builtin
    command_builtin(token);
  }
  else{                                 //not builtin
      if (execvp(token[0], token)==-1){
        printf("No such command : %s\n", token[0]);
      }
  }
  return;
}

int token_count(char ** tokens){
  int i = 0;
  while(tokens[i]!=NULL){
    i++;
  }
  return i;
}

int check_builtin(char * command){
  int k = size_built;               //number of shell commands

  for(int i = 0; i < k;i++){      //find matching builtin command
    if (strcmp(command, built[i].command) == 0){
      return 1;
    }
  }
  return 0;
}

void command_builtin(char ** tokens){
  int tkn = token_count(tokens);    //token numbers
  if (tkn == 0) return;             //for empty line
  int k = size_built;               //number of shell commands

  for(int i = 0; i < k;i++){      //find matching builtin command
    if (strcmp(tokens[0], built[i].command) == 0){
      built[i].shell_command(tkn, tokens);
    }
  }

}
