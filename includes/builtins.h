#ifndef BUILTINS_H
# define BUILTINS_H

#include "parser.h"

const char *builtins[6] = {"echo",
            "pwd",
            "cd",
            "env",
            "export",
            "unset"};

typedef struct s_env_var
{
	char *env_var;
	struct s_env_var *next;
}	t_env_var;




void echo_builtin(t_command *head);
void print_current_directory(void);
void change_directory(t_command *cmd);
void (*builtin_func[3])() = {
                                echo_builtin,
                                print_current_directory,
                                change_directory};
#endif
