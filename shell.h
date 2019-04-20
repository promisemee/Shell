//shell.h


//main
void shell_loop();

//read & parse line
int read_line(char * line);
int check_line(char * line);
void parse_line(char * line, char ** tokens);
void parse_rp(int flag, char* line, char ** tokens, char ** left, char ** right);

//execute line
int token_count(char ** tokens);

void run_default(char ** tokens);
void run_pipe(char**left, char** right);

void execute_line(char **tokens);
void execute_pipe(char ** token);

int check_builtin(char * command);
void command_builtin(char **);


//error & signal
void error(char* msg);
void handler(int);
