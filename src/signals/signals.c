/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 21:52:57 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 16:32:24 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

extern int	g_exit_status;

/*
** TODO check if SIGQUIT needs to be ignored
*/
void	init_signals(struct sigaction *sa, void (*handler)(int))
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

void	sigint_prompt_handler(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	sigint_heredoc_handler(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(130);
}

void	sigint_executor_handler(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}
