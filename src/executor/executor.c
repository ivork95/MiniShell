/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:10:13 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/15 18:57:06 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/builtins.h"
#include "../../includes/executor.h"

void	exec_ll(t_env_var *ll_environ, t_command *command)
{
	t_env_var	*path_node;
	char		*path;
	char		*full_path;

	path_node = find_env_var(ll_environ, "PATH");
	if (path_node == NULL)
	{
		printf("minishell: %s: No such file or directory\n", command->args[0]);
		exit(EXIT_FAILURE);
	}
	path = path_node->value;
	if (access(command->args[0], X_OK) == 0)
		full_path = command->args[0];
	else
		full_path = get_full_path(path, command->args[0]);
	execve(full_path, command->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	exec_builtin(t_env_var **head, t_command *cmd)
{
	size_t					i;
	static const t_builtins	lookup_table[] = {
	{"echo", &echo_builtin},
	{"pwd", &pwd_builtin},
	{"cd", &cd_builtin},
	{"env", &env},
	{"export", &export_builtin},
	{"unset", &unset_builtin},
	{"exit", &exit_builtin},
	{NULL, NULL}
	};

	i = 0;
	while (lookup_table[i].builtin_name)
	{
		if (!ft_strncmp(cmd->cmd, lookup_table[i].builtin_name,
				ft_strlen(cmd->cmd)))
		{
			lookup_table[i].function(cmd, head);
			return (1);
		}
		i++;
	}
	return (0);
}

void	child_procces(t_command *cmd, t_env_var **head, int read_end, int i, int pipe_fd[2])
{
	if (cmd->next == NULL)
		last_process(head, cmd, read_end);
	else if (i == 0)
		first_process(head, cmd, pipe_fd);
	else
		middle_process(head, cmd, pipe_fd, read_end);
}

void error_handeling(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	create_processes(t_command *cmd, t_env_var **head)
{
	int		pipe_fd[2];
	int		read_end;
	size_t	i;

	i = 0;
	read_end = -1;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				error_handeling("pipe");
		}
		cmd->cpid = fork();
		if (cmd->cpid == -1)
			error_handeling("fork");
		if (cmd->cpid == 0)
		{
			if (cmd->next == NULL)
				last_process(head, cmd, read_end);
			else if (i == 0)
				first_process(head, cmd, pipe_fd);
			else
				middle_process(head, cmd, pipe_fd, read_end);
		}
		else
		{
			if (i > 0)
			{
				if (close(read_end) == -1)
					error_handeling("close");
			}
			read_end = pipe_fd[0];
			if (cmd->next != NULL)
			{
				if (close(pipe_fd[1]) == -1)
					error_handeling("close");
			}
			i++;
			cmd = cmd->next;
		}
	}
}

void	executor(t_command *cmd, t_env_var **head)
{
	if (cmd->next == NULL)
	{
		if (exec_builtin(head, cmd))
			return ;
	}
	create_processes(cmd, head);
	while (wait(NULL) != -1)
		;
}
