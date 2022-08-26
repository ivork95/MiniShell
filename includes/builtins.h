/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:03:25 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 20:44:25 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

/*builtin functions*/
void	echo_builtin(t_command *command, t_env_var *vars);
void	print_current_directory(t_command *cmd, t_env_var *vars);
// void	change_directory(t_command *cmd, t_env_var *vars);
// void	print_env_vars(t_command *command, t_env_var *head);

t_env_var	*environ_to_linked_list_recursive(t_env_var *head, char **environ);
void		add_env_var(t_env_var **head, char *key, char *value);

static t_builtins lookup_table[] =
{
	{"echo", &echo_builtin},
	{"pwd", &print_current_directory},
	// {"cd", &change_directory},
	// {"env", &echo_builtin},
	// {"export", &echo_builtin},
	// {"unset", &echo_builtin},
	{NULL, NULL}
};

#endif
