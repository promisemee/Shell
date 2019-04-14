#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include <signal.h>

#include "shell.h"
#include "builtin.h"

#define LINESIZE 2048
#define BUFSIZE 1024

void handler(int signum){
  //handler for SIGNAL
  //does nothing yet!
  ;
}

void error(char * msg){
  //function for error and exit
  perror(msg);
  exit(0);
}

void shell_loop(){
  char line[LINESIZE];
  char ** tokens = malloc(BUFSIZE * sizeof(char*));   //default input, &
  char ** leftt = malloc(BUFSIZE * sizeof(char*));    //for redirecting and pipe
  char ** rightt = malloc(BUFSIZE * sizeof(char*));   //for redirecting and pipe
  int flag = -1;

  // signal(SIGINT, handler);
  signal(SIGTSTP, handler);

  while(1){
    printf("myshell>");             //shell prompt
    fgets(line, LINESIZE, stdin);   //read line
    flag = check_line(line);
    if (flag<0){
      error("Input Error : ");
    }
    if (flag == 0){               //default
      parse_line(line, tokens);
      execute(tokens);
    }
    else{
      parse_rp(flag, line, tokens, leftt, rightt);
      execute_rp(flag, leftt, rightt);
    }

    // tokens = parse_line(line);       //parse line
    // execute_line(tokens);            //execute line
    memset(line, 0, sizeof(line));
    memset(tokens, 0, sizeof(tokens));
    memset(leftt, 0, sizeof(leftt));
    memset(rightt, 0, sizeof(rightt));
    flag = -1;
  }

}

int check_line(char * line){
  //check line for '>', '<', '|', '&' and returns flag
  for(int i = 0; line[i]!='\0' ; i++){
    switch(line[i]){
      case '>':
        return 1;
        break;
      case '<':
        return 2;
        break;
      case '|':
        return 3;
        break;
      default:    //just alphabet/number
        break;
    }
  }
  return 0;     //default input(just alphabets)
}

void parse_line(char * line, char ** tokens){
  //cut line to tokens
  int i = 0;
  char * token;
  for(int k =0; line[k]!='\0';k++){         //ignore '\n', '\t'
    if (line[k]=='\n') line[k] = '\0';
    if (line[k]=='\t') line[k] = ' ';
  }
  token = strtok(line, " ");
  while(token!=NULL){
    tokens[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
}

void parse_rp(int flag, char * line, char ** tokens, char ** left, char ** right){
  char *symbol[] = {" ",">", "<", "|"};
  char *sym = symbol[flag];
  char * token = malloc(BUFSIZE * sizeof(char));
  for(int k = 0; line[k]!='\0'; k++){
    if (line[k]=='\t') line[k] = ' ';
  }
  tokens[0] = strtok(line, sym);
  tokens[1] = strtok(NULL, sym);
  parse_line(tokens[0], left);
  parse_line(tokens[1], right);
  free(tokens);
}


void execute(char **tokens){
    pid_t pid;
    int status;
    pid = fork();   //fork child process, pid = pid of child process
    if (pid==-1) error("can't fork:");
    if (pid==0){                      //child process
      command_line(tokens);
    }
    else{         //parent process
      waitpid(pid, &status, 0);
    }

}

void execute_rp(int flag, char**left, char** right){
  for(int i = 0; left[i]!=NULL; i++)  printf("%s", left[i]);
  printf("\n");
  for(int i = 0; right[i]!=NULL; i++)  printf("%s", right[i]);
  printf("\n");
}

int token_count(char ** tokens){
  int i = 0;
  while(tokens[i]!=NULL){
    i++;
  }
  return i;
}

void command_line(char ** tokens){
  int tkn = token_count(tokens);    //token numbers
  if (tkn == 0) return;             //for empty line
  int k = size_built;               //number of shell commands

  for(int i = 0; i < k;i++){      //find matching builtin command
    if (strcmp(tokens[0], built[i].command) == 0){
      built[i].shell_command(tkn, tokens);
    }
  }

}
//
// void execute_line(char ** tokens){
//
//   //fork()
//   pid_t pid;
//   int status;
//   pid = fork();   //fork child process, pid = pid of child process
//   if (pid==-1) error("can't fork:");
//   if (pid==0){                      //child process
//
//
//   }
//
//   else{         //parent process
//     waitpid(pid, &status, 0);
//   }
// }


//***MAIN***//

int main(void){

  shell_loop();

  return 0;
}
