/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/13 09:31:26 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	set_command(t_token **tokens, t_command *command)
{
	char	*cmd;
	size_t	i;

	cmd = malloc(sizeof(*cmd) * ((*tokens)->len + 1));
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(cmd, (*tokens)->str, (*tokens)->len + 1);
	i = count_words(*tokens);
	command->args = ft_calloc(i + 1, sizeof(char *));
	if (command->args == NULL)
		exit(EXIT_FAILURE);
	command->args[i] = NULL;
	command->args[0] = cmd;
	command->cmd = cmd;
	*tokens = (*tokens)->next;
}

void	set_args(t_token **tokens, t_command *command)
{
	size_t	i;

	i = 0;
	while (command->args[i])
		i++;
	while ((*tokens) && (*tokens)->type == WORD)
	{
		command->args[i] = malloc(sizeof(char) * (*tokens)->len + 1);
		if (command->args[i] == NULL)
			exit(EXIT_FAILURE);
		ft_strlcpy(command->args[i], (*tokens)->str, (*tokens)->len + 1);
		*tokens = (*tokens)->next;
		i++;
	}
}

void	set_files(t_token **tokens, t_command *command)
{
	t_file	*files;
	t_file	*tmp;

	files = malloc(sizeof(*files));
	if (files == NULL)
		exit(EXIT_FAILURE);
	files->type = redirect_type((*tokens)->str);
	*tokens = (*tokens)->next;
	files->file_name = malloc(sizeof(char) * (*tokens)->len + 1);
	if (files->file_name == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(files->file_name, (*tokens)->str, (*tokens)->len + 1);
	files->next = NULL;
	if (!(command)->files)
		(command)->files = files;
	else
	{
		tmp = (command)->files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = files;
	}
	*tokens = (*tokens)->next;
}

void	fill_command(t_token **tokens, t_command *command)
{
	if ((*tokens)->type == WORD && command->cmd == NULL)
		set_command(tokens, command);
	else if ((*tokens)->type == REDIRECT_OP)
		set_files(tokens, command);
	else
		set_args(tokens, command);
}

t_command	*parser(t_token *tokens)
{
	t_command	*head;
	t_command	*node;

	head = NULL;
	while (tokens)
	{
		node = create_new_command();
		while (tokens && tokens->type != PIPE)
			fill_command(&tokens, node);
		command_add_back(&head, node);
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (head);
}
