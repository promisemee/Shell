//shell.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINESIZE 2048
#define BUFSIZE 1024

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW   "\x01b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"    //for Reset!

//----
char history[BUFSIZE][LINESIZE];		
int i;
//for history function---


//main
void shell_loop();

//read & parse line
int read_line(char * line);
int check_line(char * line);
void parse_line(char * line, char ** tokens);
int parse_rp(int flag, char* line, char ** tokens);

//error & signal
void error(char* msg);
void handler(int);
