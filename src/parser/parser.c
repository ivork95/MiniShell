/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/15 05:23:35 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/builtins.h"
void	set_command(t_token **token, t_command *command)
{
	char	*cmd;
	size_t	i;

	cmd = malloc(sizeof(*cmd) * ((*token)->len + 1));
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(cmd, (*token)->str, (*token)->len + 1);
	i = count_words(*token);
	command->args = ft_calloc(i + 1, sizeof(char *));
	if (command->args == NULL)
		exit(EXIT_FAILURE);
	command->args[i] = NULL;
	command->args[0] = cmd;
	command->cmd = cmd;
	*token = (*token)->next;
}

void	set_args(t_token **token, t_command *command)
{
	size_t		i;

	i = 0;
	while (command->args[i])
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

int	heredoc_function(t_token *token)
{
	char	*user_input;
	char	*joined_str;
	char	*delimiter;
	int		pipe_fd[2];
    int fd;

	delimiter = malloc(sizeof(char) * token->len + 1);
	ft_strlcpy(delimiter, token->str, token->len + 1);
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
    fd = open("heredocccc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	while (1)
	{
		user_input = readline("heredoc>");
		if (!ft_strncmp(user_input, delimiter, ft_strlen(delimiter) + 1))
			break ;
		joined_str = ft_strjoin(user_input, "\n");
		write(fd, joined_str, ft_strlen(joined_str));
		free(user_input);
		free(joined_str);
	}
	close(pipe_fd[1]);
	return(pipe_fd[0]);
}


void	set_files(t_token **token, t_command *command)
{
	t_file	*file;
	t_file	*tmp;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		exit(EXIT_FAILURE);
    if (redirect_type((*token)->str) == HEREDOC)
		file->heredoc_fd = heredoc_function((*token)->next);
	file->type = redirect_type((*token)->str);
	*token = (*token)->next;
	file->file_name = malloc(sizeof(char) * (*token)->len + 1);
	if (file->file_name == NULL)
		exit(EXIT_FAILURE);
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
		command = create_new_command();
		while (token && token->type != PIPE)
			fill_command(&token, command);
		command_add_back(&head, command);
		if (token != NULL)
			token = token->next;
	}
	return (head);
}
