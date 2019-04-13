#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void shell_loop(){
  char line[LINESIZE];
  char ** tokens;

  signal(SIGINT, handler);
  signal(SIGTSTP, handler);

  while(1){
    printf("myshell>");             //shell prompt
    fgets(line, LINESIZE, stdin);   //read line
    tokens = parse_line(line);       //parse line
    execute_line(tokens);            //execute line
  }

}

char** parse_line(char * line){     //cuting line to tokens
  int i = 0;
  char * token;
  char ** tokens = malloc(BUFSIZE * sizeof(char*));
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
  return tokens;
}


int token_count(char ** tokens){
  int i = 0;
  while(tokens[i]!=NULL){
    i++;
  }
  return i;
}

void execute_line(char ** tokens){
  int tkn = token_count(tokens);    //token numbers
  if (tkn == 0) return;             //for empty line
  int k = size_built;               //number of shell commands
  for(int i = 0; i < k;i++){
    if (strcmp(tokens[0], built[i].command) == 0){
      built[i].shell_command(tkn, tokens);
    }
  }
}



int main(void){

  shell_loop();

  return 0;
}
