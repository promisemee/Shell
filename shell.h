//shell.h

void shell_loop();
char** parse_line(char * line);
int token_count(char ** tokens);
void execute_line(char **tokens);
void siginth(int);
