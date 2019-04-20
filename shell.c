#include <errno.h>
#include <signal.h>

#include "shell.h"
#include "builtin.h"
#include "execute.h"

#define LINESIZE 2048
#define BUFSIZE 1024
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"    //for Reset!

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

  signal(SIGINT, handler);
  signal(SIGTSTP, handler);

  while(1){
    printf(ANSI_COLOR_RED "myshell> "  ANSI_COLOR_RESET);             //shell prompt
    read_line(line);   //read line
    flag = check_line(line);
    if (flag < 0){
      error("Input Error : ");
    }
    if (flag == 0){               //default
      parse_line(line, tokens);
      run_default(tokens);
    }
    else if (flag == 3){   //for pipe line
      int pipenum = parse_rp(flag, line, tokens);
      run_pipe(pipenum, tokens);
    }
    else{
      parse_rp(flag, line, tokens);
      // execute_rp(flag, leftt, rightt);
    }
    //reset
    memset(line, 0, LINESIZE);
    memset(tokens, 0, BUFSIZE);
    memset(leftt, 0, BUFSIZE);
    memset(rightt, 0, BUFSIZE);
    flag = -1;
  }
}

int read_line(char * line){
  //read line
  char buffer[LINESIZE];
  char c;

  for(int i = 0;;i++){
    c = getchar();
    if (c == '\n' || c == EOF){
      buffer[i] = '\0';
      strcpy(line, buffer);
      break;
    }
    buffer[i] = c;
  }
  return 0;
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
  for(int k =0; line[k]!='\0';k++){         //ignore '\t'
    if (line[k]=='\t') line[k] = ' ';
  }
  token = strtok(line, " ");
  while(token!=NULL){
    tokens[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
}

int parse_rp(int flag, char * line, char ** tokens){
  char *symbol[] = {" ",">", "<", "|"};
  char *sym = symbol[flag];
  char * token;
  for(int k = 0; line[k]!='\0'; k++){
    if (line[k]=='\t') line[k] = ' ';
  }
  int i = 0;
  token = strtok(line, sym);
  while(token!=NULL){
    tokens[i] = token;
    i++;
    token = strtok(NULL, sym);
  }
  return i;
}


//***MAIN***//

int main(void){

  shell_loop();

  return 0;
}
