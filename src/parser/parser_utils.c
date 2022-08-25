#include "../../includes/parser.h"

int	redirect_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (REDIRECT_APP);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIRECT_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIRECT_OUT);
	return (-1); // kan deze case ooit afgaan? Kan een enum -1 assigned krijgen?
}

size_t	count_words(t_token *head)
{
	size_t	i;

	i = 0;
	while (head && head->type != PIPE)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	init_command(t_command *command, t_env_var **envp)
{
	command->env_vars = envp;
	command->cmd = NULL;
	command->args = NULL;
	command->files = NULL;
	command->next = NULL;
}

t_command	*create_new_command(t_env_var **envp)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	if (command == NULL)
		exit(EXIT_FAILURE);
	init_command(command, envp);
	return (command);
}

void	command_add_back(t_command **head, t_command *new)
{
	t_command	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
