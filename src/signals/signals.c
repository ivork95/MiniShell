/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 21:52:57 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/12 13:27:52 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

extern int	g_exit_status;

void	init_signals(struct sigaction *sa, void (*handler)(int))
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_prompt_handler(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	sigint_heredoc_handler(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(130);
}
