#include <errno.h>
#include <signal.h>

#include "shell.h"
#include "builtin.h"
#include "execute.h"

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

  system("clear");    //clear terminal

  printf("---------------------------------------------------------------------------\n");
  printf("\n\n");
  printf("  Welcome to Shell! ٩( ᐛ )و\n");
  printf("  Type 'help' for help or for information of this shell\n");
  printf("  Type 'q' or 'exit' to exit the shell\n\n\n");
  printf("---------------------------------------------------------------------------\n");
  printf("\n\n");

  // printf("");
  memset(history, 0, LINESIZE);
  i = 0;
  char line[LINESIZE];
  char ** tokens = malloc(BUFSIZE * sizeof(char*));   //for parsed line
  int flag = -1;
  

  signal(SIGINT, handler);
  signal(SIGTSTP, handler);

  while(1){
    printf(ANSI_COLOR_RED "myshell> "  ANSI_COLOR_RESET);             //shell prompt
    read_line(line);   //read line
    
    strcpy(history[i], line);   //history
    i++;
    
    if (strcmp(line, "q")==0) exit(0);      //quick exit
    flag = check_line(line);
    if (flag < -1){
      error("Input Error : "); 
    }
    else if(flag == -1){
      printf("Syntax Error\n");
    }
    else if (flag == 0){               //default
      parse_line(line, tokens);
      run_default(tokens);
    }
    else if (flag == 3){   //for pipe line
      int pipenum = parse_rp(flag, line, tokens);
      if (pipenum > 0) run_pipe(pipenum, tokens);
    }
    else{
      int redir = parse_rp(flag, line, tokens);
      if (redir > 2) printf("Cannot handle multiple redirection\n");
      if (redir > 0) run_redirection(flag, tokens);
    }
    //reset
    memset(line, 0, LINESIZE);
    memset(tokens, 0, BUFSIZE);
    flag = -2;
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
  if (strcmp(line, "<") == 0 || strcmp(line, ">") == 0 || strcmp(line, "|") == 0){  //syntax error
    return -1;
  }
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
