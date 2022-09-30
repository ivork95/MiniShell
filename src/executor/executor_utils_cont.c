/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils_cont.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 10:53:02 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/30 11:00:42 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

extern int	g_exit_status;

void	set_exit_status(int last_exit_status)
{
	if (WIFEXITED(last_exit_status))
		g_exit_status = WEXITSTATUS(last_exit_status);
}

void	put_exit_status(void)
{
	ft_putnbr_fd(g_exit_status, 1);
}
