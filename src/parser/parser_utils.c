/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:31:23 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/19 16:19:19 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdio.h>

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

void	init_command(t_command *command)
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
		exit(EXIT_FAILURE);
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

void	print_commands(t_command *cmds)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (cmds)
	{
		i = 0;
		printf("--------------------\n");
		printf("cmds[%lu]\n", j);
		printf("command = %s\n", cmds->cmd);
		while (cmds->args && cmds->args[i])
		{
			printf("args[%lu] = %s\n", i, cmds->args[i]);
			i++;
		}
		while (cmds->files)
		{
			printf("file operattor = %d\nfile_name  = %s\n",
				cmds->files->type, cmds->files->file_name);
			cmds->files = cmds->files->next;
		}
		printf("--------------------\n");
		cmds = cmds->next;
		j++;
	}
}
