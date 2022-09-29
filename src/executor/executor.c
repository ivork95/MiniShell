/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:10:13 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/29 08:16:38 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/signals.h"
#include <signal.h>

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
	int					*pipe_fd;
	int					read_end;
	size_t				i;
	struct sigaction	sa;

	i = 0;
	read_end = -1;
	init_signals(&sa, sigint_executor_handler);
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
			copy_read_end(&read_end, pipe_fd);
		i++;
		cmd = cmd->next;
	}
}

void	update_exit_code(int last_exit_status, t_env_var **head)
{
	char	*s;
	char	*ascii;

	s = (void *)0;
	if (WIFEXITED(last_exit_status))
	{
		ascii = ft_itoa(WEXITSTATUS(last_exit_status));
		if (ascii == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
		s = ft_strjoin("?=", ascii);
		free(ascii);
		if (s == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
		add_env_var(head, s);
		free(s);
	}
}

void	executor(t_command *cmd, t_env_var **head)
{
	int		r;
	int		last_exit_status;
	pid_t	pid_to_check;

	if (cmd->next == NULL)
	{
		if (exec_builtin(head, cmd))
			return ;
	}
	create_processes(cmd, head);
	while (cmd->next != NULL)
		cmd = cmd->next;
	r = 0;
	last_exit_status = 0;
	pid_to_check = wait(&r);
	while (pid_to_check != -1)
	{
		if (pid_to_check == cmd->cpid)
			last_exit_status = r;
		pid_to_check = wait(&r);
	}
	update_exit_code(last_exit_status, head);
}
