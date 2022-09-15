/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:12:32 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/15 17:58:04 by ivork         ########   odam.nl         */
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
#include "../../includes/executor.h"

static void	handle_redirect_in(t_file *files)
{
	int	fd;

	while (files)
	{
        if (files->type == HEREDOC)
        {
            fd = open("heredoc_tmp.txt", O_RDONLY);
		    if (dup2(files->heredoc_fd, STDIN_FILENO) == -1)
		    	ft_putendl_fd("Error: Could not duplicate fd", 2);
		    if (close(files->heredoc_fd) == -1)
	    		ft_putendl_fd("Error: could not close fd", 2);
            files = files->next;
            break;
        }
		if (files->type == REDIRECT_OUT)
		{
			files = files->next;
			continue ;
		}
		else if (files->type == REDIRECT_IN)
			fd = open(files->file_name, O_RDONLY);
		if (fd == -1)
			ft_putendl_fd("Error: opening file", 2);
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_putendl_fd("Error: Could not duplicate fd", 2);
		if (close(fd) == -1)
			ft_putendl_fd("Error: could not close fd", 2);
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
			ft_putendl_fd("Error: opening file", 2);
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_putendl_fd("Error: Could not duplicate fd", 2);
		if (close(fd) == -1)
			ft_putendl_fd("Error: could not close fd", 2);
		files = files->next;
	}
}

void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2])
{
	// handle first process
	//TODO add exec_builtin functin

	if (close(pipe_fd[0]) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (close(pipe_fd[1]) == -1)
		exit(EXIT_FAILURE);
	if (cmd->files != NULL)
	{
		// er is een redirect in/redirect out
		handle_redirect_in(cmd->files);
	}
	if (exec_builtin(head, cmd))
		exit(EXIT_SUCCESS);
	exec_ll(*head, cmd);
}

void	middle_process(t_env_var **head, t_command *cmd, int pipe_fd[2], int read_end)
{
	// handle middle process
	if (close(pipe_fd[0]) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1 || dup2(read_end, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (close(pipe_fd[1]) == -1)
		exit(EXIT_FAILURE);
	if (close(read_end) == -1)
		exit(EXIT_FAILURE);
	if (cmd->files != NULL)
	{
		handle_redirect_in(cmd->files);
		handle_redirect_out(cmd->files);
	}
	if (exec_builtin(head, cmd))
		exit(EXIT_SUCCESS);
	exec_ll(*head, cmd);
}

void	last_process(t_env_var **head, t_command *cmd, int read_end)
{
	// handle last process
	if (read_end != -1)
	{
		if (dup2(read_end, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (close(read_end) == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd->files != NULL)
	{
		// er is een redirect in/redirect out
		handle_redirect_in(cmd->files);
		handle_redirect_out(cmd->files);
	}
	if (exec_builtin(head, cmd))
		exit(EXIT_SUCCESS);
	exec_ll(*head, cmd);
}