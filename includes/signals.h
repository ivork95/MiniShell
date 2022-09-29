/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 22:02:05 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/29 08:20:42 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	init_signals(struct sigaction *sa, void (*handler)(int));
void	sigint_prompt_handler(int num);
void	sigint_heredoc_handler(int num);
void	sigint_executor_handler(int num);

#endif
