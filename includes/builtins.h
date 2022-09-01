/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:03:25 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/01 15:24:42 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* Public libraries */
# include <stddef.h>

/* Private libraries */
# include "structs.h"
# include "../src/libft/libft.h"

/* env.c */
void		free_env_vars(t_env_var *head);
void		env(t_command *command, t_env_var **vars);
void		put_env_vars_declare(t_env_var *head);
t_env_var	*environ_to_linked_list_recursive(t_env_var *head, char **environ);

/* export.c */
t_env_var	*assign_env_key_value(char *env_var, char *ptr);
void		add_env_var(t_env_var **head, char *env_var);
void	export_builtin(t_command *command, t_env_var **environ);

/* unset.c */
void		search_and_destroy(t_env_var **head, char *key);
void		unset_builtin(t_command *command, t_env_var **environ);

/* echo.c */
void		echo_builtin(t_command *command, t_env_var **vars);

/* pwd.c */
void		print_current_directory(t_command *cmd, t_env_var **vars);

/* change_dir.c */
void		change_directory(t_command *cmd, t_env_var **vars);

static t_builtins	lookup_table[] = {
{"echo", &echo_builtin},
{"pwd", &print_current_directory},
{"cd", &change_directory},
{"env", &env},
{"export", &export_builtin},
	// {"unset", &echo_builtin},
{NULL, NULL}
};

#endif
