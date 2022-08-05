/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/05 15:54:27 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_quote_type(char *str)
{
	if (*str == '\'')
		return (SINGLE_QUOTES);
	else if (*str == '\"')
		return (DOUBLE_QUOTES);
	return (0);
}

void	init_command(t_command **command)
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

void	set_command(t_token **token, t_command **command)
{
	char	*cmd;

	if ((*token)->quoted)
	{
		(*token)->str++;
		(*token)->len -= 2;
	}
	cmd = malloc(sizeof(char) * (*token)->len + 1);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(cmd, (*token)->str, (*token)->len + 1);
	(*command)->cmd = cmd;
	*token = (*token)->next;
}

void	set_args(t_token **token, t_command **command)
{
	t_token	*tmp;
	size_t		i;
	int			quotes;
	
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
		exit(EXIT_FAILURE);
	(*command)->args[i + 1] = NULL;
	i = 0;
	(*command)->args[i] = (*command)->cmd;
	i++;
	while ((*token) && (*token)->type == WORD)
	{
		if ((*token)->quoted)
		{
			quotes = check_quote_type((*token)->str); // quotes variabel word niet gebruikt?
			(*token)->str++;
			(*token)->len -= 2;
		}
		
		(*command)->args[i] = malloc(sizeof(char) * (*token)->len + 1);
		if ((*command)->args[i] == NULL)
			exit(EXIT_FAILURE);
		ft_strlcpy((*command)->args[i], (*token)->str, (*token)->len + 1);
		*token = (*token)->next;
		i++;
	}
}

void	set_files(t_token **token, t_command **command)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		exit(EXIT_FAILURE);
	file->type = redirect_type((*token)->str);
	*token = (*token)->next;
	if ((*token)->quoted)
	{
		(*token)->str++;
		(*token)->len -= 2;
	}
	file->file_name = malloc(sizeof(char) * (*token)->len + 1);
	if (file->file_name == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(file->file_name, (*token)->str, (*token)->len + 1);
	(*command)->files = file;
	*token = (*token)->next;
}

void	fill_command(t_token **token, t_command **command)
{
	if ((*token)->type == WORD && (*command)->cmd == NULL)
		set_command(token, command);
	else if ((*token)->type == REDIRECT_OP)
		set_files(token, command);
	else
		set_args(token, command);
}

t_command	*parser(t_token *token)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	if (command == NULL)
		exit(EXIT_FAILURE);
	init_command(&command);
	while (token && token->type != PIPE)
	{
		fill_command(&token, &command);
	}
	return (command);
}
