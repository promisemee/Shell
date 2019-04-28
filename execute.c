#include <sys/stat.h>
#include <fcntl.h>

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


void run_pipe(int pn, char ** tokens){
  int fd[2];
  pid_t pid, mpid;
  int fd_b, i;
  i = 0;
  int status;
  char ** command = malloc(BUFSIZE * sizeof(char*));
  char ** temp = malloc(BUFSIZE * sizeof(char*));

  parse_line(tokens[i], command);

  mpid = fork();

  if (mpid<0) error("can't fork:");

  if (mpid == 0){
    while(command != NULL){   //repeat untill end of command
      pipe(fd);
      pid = fork();
      if (pid<0){
        error("can't fork : ");
      }
      if (pid == 0){
        dup2(fd_b, 0);
        if (tokens[i+1]!='\0'){
          dup2(fd[1], 1);
        }
        close(fd[0]);
        execute_child(command);
        exit(0);
      }
      else{
        wait(NULL);
        close(fd[1]);
        fd_b = fd[0];
        i++;
        if (tokens[i] == '\0')  command = NULL;
        else  parse_line(tokens[i], command);
      }
    }
    exit(0);
  }
  else{
    waitpid(mpid, &status, 0);

  }
}

void run_redirection(int flag, char ** token){
  //cannot handle multiple redirection!
  int fd[2];
  int file, status;
  pid_t pid;
  
  char ** left = malloc(BUFSIZE*sizeof(char*));
  char ** right = malloc(BUFSIZE*sizeof(char*));
  parse_line(token[0], left); 
  parse_line(token[1], right);

  if (flag == 1){   //redirection for >
    pid = fork();
    if (pid<0) error("can't fork");
    if (pid==0){
      if (file = open(right[0], O_CREAT | O_TRUNC | O_WRONLY, 0644)==-1){
        error("File Error");
      }
      if (dup2(file, STDOUT_FILENO)==-1){
        error("dup error");
      }
      execute_child(left);
      close(file);
      exit(0);
    }
    else{
      waitpid(pid, &status, 0);
    }
  }
  if (flag == 2){   //redirection for <
    pid = fork();
    if (pid<0) error("can't fork");
    if (pid==0){
      if (file = open(left[0], O_RDONLY)==-1){
        error("File Error");
      }
      if (dup2(file, 0)==-1){
        error("dup error");
      }
      execute_child(right);
      close(file);

      exit(0);
    }
    else waitpid(pid, &status, 0);
  }
}

void execute_child(char**command){
  if (check_builtin(command[0])==1){      //builtin
    command_builtin(command);
  }
  else{                                 //not builtin
      if (execvp(command[0], command)==-1){
        printf("%s : No such command\n", command[0]);
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
