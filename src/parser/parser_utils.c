/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:31:23 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/23 14:33:06 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	redirect_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (REDIRECT_APP);
	else if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIRECT_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIRECT_OUT);
	return (-1);
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

static void	init_command(t_command *command)
{
	command->cmd = NULL;
	command->args = NULL;
	command->files = NULL;
	command->cpid = -1;
	command->next = NULL;
}

t_command	*create_new_command(void)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	if (command == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	init_command(command);
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
