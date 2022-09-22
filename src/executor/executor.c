/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:10:13 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/22 13:36:21 by kgajadie      ########   odam.nl         */
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
				ft_strlen(lookup_table[i].builtin_name)))
		{
			lookup_table[i].function(cmd, head);
			return (1);
		}
		i++;
	}
	return (0);
}

void	create_processes(t_command *cmd, t_env_var **head)
{
	int		*pipe_fd;
	int		read_end;
	size_t	i;

	i = 0;
	read_end = -1;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			pipe_fd = create_pipe();
		if (cmd->next == NULL)
			last_process(head, cmd, read_end);
		else if (i == 0)
			first_process(head, cmd, pipe_fd);
		else
			middle_process(head, cmd, pipe_fd, read_end);
		if (i > 0)
			close_pipe(read_end);
		if (cmd->next != NULL)
		{
			read_end = pipe_fd[0];
			close_pipe(pipe_fd[1]);
		}
		i++;
		cmd = cmd->next;
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

	/*
	while (cmd->next != NULL)
	{
		cmd = cmd->next;
	}
	int r = 0;
	int last_exit_status = 0;
	pid_t pid_to_check = wait(&r);
	while (pid_to_check != -1)
	{
		printf("pid_to_check = %i\n", pid_to_check);
		printf("cmd->cpid = %i\n", cmd->cpid);
		if (pid_to_check == cmd->cpid)
		{
			printf("r = %i\n", r);
			last_exit_status = r;
		}
		pid_to_check = wait(&r);
	}
	if (WIFEXITED(last_exit_status))
		printf("last_exit_status = %i\n", WEXITSTATUS(last_exit_status));
	*/

	while (wait(NULL) != -1)
		;
}
