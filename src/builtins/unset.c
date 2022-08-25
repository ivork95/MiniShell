#include "../../includes/parser.h"

void delete_node(t_env_var **head, char *key)
{
	t_env_var	*tmp;
	t_env_var *envp;
	tmp = NULL;
	envp = *head;
	while (envp)
	{
		if (!ft_strncmp(key, envp->key, ft_strlen(key)))
		{
			if (!tmp)
			{
				tmp = *head;
				*head = envp->next;
			}
			else
			{
				tmp->next = envp->next;
				tmp = envp;
			}
			tmp->next = NULL;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		tmp = envp;
		envp = envp->next;
	}
	return ;
}

void delete_env_var(t_command *command)
{
	char *key;
	size_t i;

	i = 1;
	while (command->args[i])
	{
		key = command->args[i];
		delete_node(command->env_vars, key);
		i++;
	}
}