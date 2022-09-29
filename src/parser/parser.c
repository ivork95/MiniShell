/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/29 17:13:56 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/builtins.h"

static void	set_command(t_token **token, t_command *command)
{
	char	*cmd;
	size_t	i;

	cmd = malloc(sizeof(*cmd) * ((*token)->len + 1));
	if (cmd == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	ft_strlcpy(cmd, (*token)->str, (*token)->len + 1);
	i = count_words(*token);
	command->args = ft_calloc(i + 1, sizeof(char *));
	if (command->args == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	command->args[i] = NULL;
	command->args[0] = cmd;
	command->cmd = cmd;
	*token = (*token)->next;
}

static void	set_args(t_token **token, t_command *command)
{
	size_t	i;

	i = 0;
	while (command->args[i])
		i++;
	while ((*token) && (*token)->type == WORD)
	{
		command->args[i] = malloc(sizeof(char) * (*token)->len + 1);
		if (command->args[i] == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
		ft_strlcpy(command->args[i], (*token)->str, (*token)->len + 1);
		*token = (*token)->next;
		i++;
	}
}

char	*get_file_name(t_token *token)
{
	char	*file_name;

	file_name = malloc(sizeof(char) * token->len + 1);
	if (file_name == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	ft_strlcpy(file_name, token->str, token->len + 1);
	return (file_name);
}

static void	file_add_back(t_command **command, t_file *file)
{
	t_file	*tmp;

	tmp = (*command)->files;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = file;
}

static int	set_files(t_token **token, t_command *command, t_env_var **envp)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	file->type = redirect_type((*token)->str);
	*token = (*token)->next;
	if (file->type == HEREDOC)
	{
		file->file_name = create_file_name();
		file->next = NULL;
		if (heredoc_function(*token, file->file_name, envp) == -1)
		{
			unlink(file->file_name);
			free(file->file_name);
			free(file);
			return (-1);
		}
	}
	else
	{
		file->file_name = get_file_name(*token);
		file->next = NULL;
	}
	if (!(command)->files)
		(command)->files = file;
	else
		file_add_back(&command, file);
	*token = (*token)->next;
	return (0);
}

static int	fill_command(t_token **token, t_command *command, t_env_var **envp)
{
	if ((*token)->type == WORD && command->cmd == NULL)
		set_command(token, command);
	else if ((*token)->type == REDIRECT_OP)
	{
		if (set_files(token, command, envp) == -1)
			return (-1);
	}
	else
		set_args(token, command);
	return (0);
}

t_command	*parser(t_token *token, t_env_var **envp)
{
	t_command	*head;
	t_command	*command;

	head = NULL;
	while (token)
	{
		command = create_new_command();
		while (token && token->type != PIPE)
		{
			if (fill_command(&token, command, envp) == -1)
			{
				printf("fill command failure\n");
				free_commands(command);
				return (NULL);
			}
		}
		command_add_back(&head, command);
		if (token != NULL)
			token = token->next;
	}
	return (head);
}
