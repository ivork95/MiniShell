/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:03:25 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 15:54:26 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

void	echo_builtin(t_command *head, char **envp);

static t_builtins lookup_table[] =
{
	{"echo", &echo_builtin},
	{"pwd", &echo_builtin},
	{"cd", &echo_builtin},
	{"env", &echo_builtin},
	{"export", &echo_builtin},
	{"unset", &echo_builtin},
	{NULL, NULL}
};

#endif
