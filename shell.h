//shell.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINESIZE 2048
#define BUFSIZE 1024

//main
void shell_loop();

//read & parse line
int read_line(char * line);
int check_line(char * line);
void parse_line(char * line, char ** tokens);
int parse_rp(int flag, char* line, char ** tokens);

//execute line -> execute.c
// int token_count(char ** tokens);
//
// void run_default(char ** tokens);
// void run_pipe(char**left, char** right);
//
// void execute_line(char **tokens);
// void execute_pipe(char ** token);
//
// int check_builtin(char * command);
// void command_builtin(char **);


//error & signal
void error(char* msg);
void handler(int);
