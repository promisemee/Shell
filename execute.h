

int token_count(char ** tokens);

void run_default(char ** tokens);
void run_pipe(int pipenum, char ** tokens);

void execute_line(char **tokens);
void execute_pipe(char ** tokens);

int check_builtin(char * command);
void command_builtin(char **);


// pipeline(char ***cmd)
// {
// 	int fd[2];
// 	pid_t pid;
// 	int fdd = 0;				/* Backup */
//
// 	while (*cmd != NULL) {
// 		pipe(fd);				/* Sharing bidiflow */
// 		if ((pid = fork()) == -1) {
// 			perror("fork");
// 			exit(1);
// 		}
// 		else if (pid == 0) {
// 			dup2(fdd, 0);
// 			if (*(cmd + 1) != NULL) {
// 				dup2(fd[1], 1);
// 			}
// 			close(fd[0]);
// 			execvp((*cmd)[0], *cmd);
// 			exit(1);
// 		}
// 		else {
// 			wait(NULL); 		/* Collect childs */
// 			close(fd[1]);
// 			fdd = fd[0];
// 			cmd++;
// 		}
// 	}
// }
