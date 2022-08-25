#include "../../includes/parser.h"

void export_env_var(t_command *command)
{
	char *key;
	char *value;
	t_env_var *head;

	i = 1;
	head = command->env_vars;
	key = command->args[i]
	delete_env_var(&head, key)
}