//built in functions //


void shell_exit(int argc, char* argv[]);
void shell_hi(int argc, char* argv[]);
void shell_cd(int argc, char* argv[]);
// void shell_fg(int argc, char* argv[]);
// void shell_bg(int argc, char* argv[]);
// void shell_job(int argc, char* argv[]);
void shell_help(int argc, char* argv[]);
void shell_builtin(int argc, char *argv[]);
void shell_history(int argc, char * argv[]);

int size_built;

struct command {
  char *command;
  char *builtin;
  void (*shell_command)(int argc, char* argv[]);
};

extern struct command built[100];
