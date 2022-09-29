/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 14:30:20 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/29 08:20:51 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Public libraries */
# include <stdlib.h>
# include <stdio.h>

/* Private libraries */
# include "structs.h"

void	perror_and_exit(char *s, int n);
void	print_commands(t_command *cmds);

#endif /* minishell.h */