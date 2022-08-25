#ifndef BUILTINS_H
# define BUILTINS_H

# include "parser.h"

t_env_var *environ_to_linked_list_recursive(t_env_var *head, char** environ);

void echo_builtin(t_command *head);
void print_current_directory(void);
void change_directory(t_command *head);
void print_env_vars(t_command *head);
void delete_env_var(t_command *head);
void delete_node(t_env_var **head, char *key);
#endif
