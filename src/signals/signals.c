/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 21:52:57 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/29 11:21:19 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

void	init_signals(struct sigaction *sa, void (*handler)(int))
{
	//TODO check if SIGQUIT needs to be ignored
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
