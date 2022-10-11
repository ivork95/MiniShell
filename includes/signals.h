/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 22:02:05 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/11 11:21:04 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/*public libraries*/
# include <signal.h>

/*private libraries*/
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

void	init_signals(struct sigaction *sa, void (*handler)(int));
void	sigint_prompt_handler(int num);
void	sigint_heredoc_handler(int num);
void	sigint_executor_handler(int num);

#endif
