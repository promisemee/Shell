int token_count(char ** tokens);

void run_default(char ** tokens);
void run_pipe(int pipenum, char ** tokens);
void run_redirection(int flag, char ** token);


void execute_child(char ** command);

int check_builtin(char * command);
void command_builtin(char **);
