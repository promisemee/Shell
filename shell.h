//shell.h

void error(char* msg);
void shell_loop();
int check_line(char * line);
void parse_line(char * line, char ** tokens);
int token_count(char ** tokens);
void execute_line(char **tokens);
void handler(int);

void command_line(char **);






//////////////////

void parse_rp(int flag, char* line, char ** tokens, char ** left, char ** right);


void execute(char ** tokens);
void execute_rp(int flag, char**left, char** right);
