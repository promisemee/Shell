

int token_count(char ** tokens);

void run_default(char ** tokens);
void run_pipe(char**left, char** right);

void execute_line(char **tokens);
void execute_pipe(char ** token);

int check_builtin(char * command);
void command_builtin(char **);
