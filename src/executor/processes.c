/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:12:32 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/29 08:16:51 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include <signal.h>

static void	handle_redirect_in(t_file *files)
{
	int	fd;

	while (files)
	{
		if (files->type == HEREDOC)
		{
			fd = open(files->file_name, O_RDONLY);
			if (fd == -1)
				perror_and_exit("open", EXIT_FAILURE);
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
			if (close(fd) == -1)
				perror("close");
			unlink(files->file_name);
		}
		if (files->type == REDIRECT_IN)
		{
			fd = open(files->file_name, O_RDONLY);
			if (fd == -1)
				perror_and_exit("open", EXIT_FAILURE);
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("dup2");
			if (close(fd) == -1)
				perror("close");
		}
		files = files->next;
	}
}

static void	handle_redirect_out(t_file *files)
{
	int	fd;

	while (files)
	{
		if (files->type == REDIRECT_IN || files->type == HEREDOC)
		{
			files = files->next;
			continue ;
		}
		else if (files->type == REDIRECT_OUT)
			fd = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (files->type == REDIRECT_APP)
			fd = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
			perror("open");
		if (dup2(fd, STDOUT_FILENO) == -1)
			perror("dup2");
		if (close(fd) == -1)
			perror("close");
		files = files->next;
	}
}

void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2])
{
	cmd->cpid = fork();
	if (cmd->cpid == -1)
		perror_and_exit("fork", EXIT_FAILURE);
	if (cmd->cpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (close(pipe_fd[0]) == -1)
			perror_and_exit("close", EXIT_FAILURE);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror_and_exit("dup2", EXIT_FAILURE);
		if (close(pipe_fd[1]) == -1)
			perror_and_exit("close", EXIT_FAILURE);
		if (cmd->files != NULL)
		{
			handle_redirect_in(cmd->files);
		}
		if (exec_builtin(head, cmd))
			exit(EXIT_SUCCESS);
		exec_ll(*head, cmd);
	}
}

void	middle_process(t_env_var **head, t_command *cmd, int pipe_fd[2],
						int read_end)
{
	cmd->cpid = fork();
	if (cmd->cpid == -1)
		perror_and_exit("fork", EXIT_FAILURE);
	if (cmd->cpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (close(pipe_fd[0]) == -1)
			perror_and_exit("close", EXIT_FAILURE);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1
			|| dup2(read_end, STDIN_FILENO) == -1)
			perror_and_exit("dup2", EXIT_FAILURE);
		if (close(pipe_fd[1]) == -1)
			perror_and_exit("close", EXIT_FAILURE);
		if (close(read_end) == -1)
			perror_and_exit("close", EXIT_FAILURE);
		if (cmd->files != NULL)
		{
			handle_redirect_in(cmd->files);
			handle_redirect_out(cmd->files);
		}
		if (exec_builtin(head, cmd))
			exit(EXIT_SUCCESS);
		exec_ll(*head, cmd);
	}
}

void	last_process(t_env_var **head, t_command *cmd, int read_end)
{
	cmd->cpid = fork();
	if (cmd->cpid == -1)
		perror_and_exit("fork", EXIT_FAILURE);
	if (cmd->cpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (read_end != -1)
		{
			if (dup2(read_end, STDIN_FILENO) == -1)
				perror_and_exit("dup2", EXIT_FAILURE);
			if (close(read_end) == -1)
				perror_and_exit("close", EXIT_FAILURE);
		}
		if (cmd->files != NULL)
		{
			handle_redirect_in(cmd->files);
			handle_redirect_out(cmd->files);
		}
		if (exec_builtin(head, cmd))
			exit(EXIT_SUCCESS);
		exec_ll(*head, cmd);
	}
}
