//shell.h

void shell_loop();
char** parse_line(char * line);
void execute_line(char **tokens);
