/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 14:30:20 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/10/06 13:54:39 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Public libraries */
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

/* Private libraries */
# include "structs.h"
# include "parser.h"
# include "expander.h"
# include "builtins.h"
# include "executor.h"
# include "signals.h"

void	perror_and_exit(char *s, int n);
void	print_commands(t_command *cmds);

#endif /* minishell.h */