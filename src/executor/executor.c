/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 10:41:45 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/14 12:51:24 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	err_func(char *str, int code)
{
	perror(str);
	exit(code);
}

static void	assign_pipe_fds(int *pipe_fd, t_command *commands)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (commands->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
			err_func("pipe", EXIT_FAILURE);
	}
}

static void	handle_processes(t_command **commands,
	t_env_var **environ, int *pipe_fd)
{
	unsigned int	i;
	int				read_end;

	i = 0;
	read_end = -1;
	if ((*commands)->cpid == 0)
	{
		if ((*commands)->next == NULL)
			last_process(environ, *commands, read_end);
		else if (i == 0)
			first_process(environ, *commands, pipe_fd);
		else
			middle_process(environ, *commands, pipe_fd, read_end);
	}
	else
	{
		read_end = pipe_fd[0];
		if (pipe_fd[1] != -1)
		{
			if (close(pipe_fd[1]) == -1)
				err_func("close", EXIT_FAILURE);
		}
		i++;
		*commands = (*commands)->next;
	}
}

static void	executor_inner(t_command *commands, t_env_var **environ)
{
	int		pipe_fd[2];

	while (commands != NULL)
	{
		assign_pipe_fds(pipe_fd, commands);
		commands->cpid = fork();
		if (commands->cpid == -1)
			err_func("fork", EXIT_FAILURE);
		handle_processes(&commands, environ, pipe_fd);
	}
}

void	executor(t_command *commands, t_env_var **environ)
{
	if (commands->next == NULL)
		if (exec_builtin(environ, commands))
			return ;
	executor_inner(commands, environ);
	while (wait(NULL) != -1)
		;
}
