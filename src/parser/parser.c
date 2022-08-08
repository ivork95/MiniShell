/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/08 22:51:27 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

void	init_command(t_command **command)
{
	(*command)->cmd = NULL;
	(*command)->args = NULL;
	(*command)->files = NULL;
	(*command)->next = NULL;
}

t_command	*create_new_node(void)
{
	t_command *command;

	command = malloc(sizeof(*command));
	if (command == NULL)
		exit(EXIT_FAILURE);
	init_command(&command);
	return (command);
}

void	command_add_back(t_command **head, t_command *new)
{
	t_command *tmp;
	
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

size_t	redirect_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (REDIRECT_APP);
	else if (!ft_strncmp(str, "<", 1))
		return (REDIRECT_IN);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIRECT_OUT);
	return (-1);
}

void	set_command(t_token **token, t_command *command)
{
	char	*cmd;

	cmd = malloc(sizeof(char) * (*token)->len + 1);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(cmd, (*token)->str, (*token)->len + 1);
	command->cmd = cmd;
	*token = (*token)->next;
}

void	set_args(t_token **token, t_command *command)
{
	t_token	*tmp;
	size_t		i;

	tmp = *token;
	i = 0;
	while (tmp && tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	command->args = malloc(sizeof(char *) * (i + 2));
	if (command->args == NULL)
		exit(EXIT_FAILURE);
	command->args[i + 1] = NULL;
	i = 0;
	command->args[i] = command->cmd;
	i++;
	while ((*token) && (*token)->type == WORD)
	{
		command->args[i] = malloc(sizeof(char) * (*token)->len + 1);
		if (command->args[i] == NULL)
			exit(EXIT_FAILURE);
		ft_strlcpy(command->args[i], (*token)->str, (*token)->len + 1);
		*token = (*token)->next;
		i++;
	}
}

void	set_files(t_token **token, t_command *command)
{
	t_file	*file;
	t_file *tmp;

	file = malloc(sizeof(t_file));
	file->file_name = malloc(sizeof(char) * (*token)->len + 1);
	if (file->file_name == NULL)
		exit(EXIT_FAILURE);
	file->type = redirect_type((*token)->str);
	*token = (*token)->next;
	ft_strlcpy(file->file_name, (*token)->str, (*token)->len + 1);
	file->next = NULL;
	if (!(command)->files)
		(command)->files = file;
	else
	{
		tmp = (command)->files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = file;
	}
	*token = (*token)->next;
}

void	fill_command(t_token **token, t_command *command)
{
	if ((*token)->type == WORD && command->cmd == NULL)
		set_command(token, command);
	else if ((*token)->type == REDIRECT_OP)
		set_files(token, command);
	else
		set_args(token, command);
}

t_command	*parser(t_token *token)
{
	t_command	*head;
	t_command	*command;

	head = NULL;
	while (token)
	{
		command = create_new_node();
		while (token && token->type != PIPE)
			fill_command(&token, command);
		command_add_back(&head, command);
		if (token != NULL)
			token = token->next;
	}
	return (head);
}
