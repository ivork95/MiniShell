/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/07/28 11:33:24 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

void	init_command(t_commands **command)
{
	(*command)->cmd = NULL;
	(*command)->args = NULL;
	(*command)->files = NULL;
	(*command)->next = NULL;
}

size_t	redirect_type(char *str)
{
	if (ft_strncmp(str, "<", 2))
		return (REDIRECT_IN);
	if (ft_strncmp(str, ">", 2))
		return (REDIRECT_OUT);
	if (ft_strncmp(str, ">>", 2))
		return (REDIRECT_APP);
	return (-1);
}

void	set_command(t_tokens **token, t_commands **command)
{
	char	*cmd;

	cmd = malloc(sizeof(char) * (*token)->len + 1);
	if (cmd == NULL)
	{
		//todo exit mallc error
		exit(0);
	}
	ft_strlcpy(cmd, (*token)->str, (*token)->len + 1);
	(*command)->cmd = cmd;
	*token = (*token)->next;
}

void	set_args(t_tokens **token, t_commands **command)
{
	t_tokens	*tmp;
	size_t		i;

	tmp = *token;
	i = 0;
	while (tmp && tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	printf("amount of args %ld\n", i);
	(*command)->args = malloc(sizeof(char *) * (i + 2));
	if ((*command)->args == NULL)
	{
		// error check
		exit(0);
	}
	(*command)->args[i + 1] = NULL;
	i = 0;
	(*command)->args[i] = (*command)->cmd;
	i++;
	while ((*token) && (*token)->type == WORD)
	{
		(*command)->args[i] = malloc(sizeof(char) * (*token)->len + 1);
		if ((*command)->args[i] == NULL)
		{
			//todo exit mallc error
			exit(0);
		}
		ft_strlcpy((*command)->args[i], (*token)->str, (*token)->len + 1);
		*token = (*token)->next;
		i++;
	}
}

void	set_files(t_tokens **token, t_commands **command)
{
	t_files	*file;

	file = malloc(sizeof(t_files));
	file->file_name = malloc(sizeof(char) * (*token)->len + 1);
	if (file->file_name == NULL)
	{
		//todo exit malloc error;
		exit(0);
	}
	file->type = redirect_type((*token)->str);
	*token = (*token)->next;
	ft_strlcpy(file->file_name, (*token)->str, (*token)->len + 1);
	(*command)->files = file;
	*token = (*token)->next;
}

void	fill_command(t_tokens **token, t_commands **command)
{
	if ((*token)->type == WORD && (*command)->cmd == NULL)
		set_command(token, command);
	else if ((*token)->type == REDIRECT_OP)
		set_files(token, command);
	else
		set_args(token, command);
}

t_commands	*parser(t_tokens *token)
{
	t_commands	*command;

	command = malloc(sizeof(*command));
	init_command(&command);
	while (token && token->type != PIPE)
	{
		fill_command(&token, &command);
	}
	return (command);
}
