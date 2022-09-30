/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils_cont.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 10:53:02 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/30 19:05:19 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

extern int	g_exit_status;

void	set_exit_status(int last_exit_status)
{
	if (WIFSIGNALED(last_exit_status))
	{
		if (WTERMSIG(last_exit_status) == 2)
			g_exit_status = 1;
		else if (WTERMSIG(last_exit_status) == 3)
			g_exit_status = 131;
	}
	if (WIFEXITED(last_exit_status))
		g_exit_status = WEXITSTATUS(last_exit_status);	
}

void	put_exit_status(void)
{
	ft_putnbr_fd(g_exit_status, 1);
}

void	open_dup_close_guards(int fd)
{
	if (fd == -1)
		perror_and_exit("open", EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		perror_and_exit("dup2", EXIT_FAILURE);
	if (close(fd) == -1)
		perror_and_exit("close", EXIT_FAILURE);
}
