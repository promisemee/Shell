#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define LINESIZE 2048
#define BUFSIZE 1024

void shell_loop(){
  char line[LINESIZE];
  char **token;

  while(1){
    printf("myshell>");             //shell prompt
    fgets(line, LINESIZE, stdin);   //read line
    token = parse_line(line);       //parse line
    execute_line(token);            //execute line
  }

}

char** parse_line(char * line){     //cuting line to tokens
  int i = 0;
  char * token;
  char ** tokens = malloc(BUFSIZE * sizeof(char*));
  token = strtok(line, " ");
  while(token!=NULL){
    tokens[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
  return tokens;
}

void execute_line(char ** tokens){
  if (strcmp(tokens[0], "\n") == 0)  return;    //for empty line
  printf("Wait...\n");
}



int main(void){

  shell_loop();

  return 0;
}
