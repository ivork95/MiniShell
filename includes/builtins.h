/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:03:25 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/15 15:49:23 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* Private libraries */
# include "structs.h"
# include "../src/libft/libft.h"

/* Public libraries */
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

/* env.c */
void		free_env_vars(t_env_var *head);
void		env(t_command *command, t_env_var **vars);
void		put_env_vars_declare(t_env_var *head);
t_env_var	*environ_to_linked_list_recursive(t_env_var *head, char **environ);
t_env_var	*find_env_var(t_env_var *head, char *key_to_check);

/* export.c */
t_env_var	*assign_env_key_value(char *env_var, char *ptr);
void		add_env_var(t_env_var **head, char *env_var);
void		export_builtin(t_command *command, t_env_var **environ);

/* unset.c */
void		search_and_destroy(t_env_var **head, char *key);
void		unset_builtin(t_command *command, t_env_var **environ);
void		delete_env_var(t_env_var **head, t_env_var *prev, t_env_var *envp);

/* echo.c */
void		echo_builtin(t_command *command, t_env_var **vars);

/* pwd.c */
void		pwd_builtin(t_command *cmd, t_env_var **vars);

/* change_dir.c */
void		cd_builtin(t_command *cmd, t_env_var **vars);

/* exit.c */
void		exit_builtin(t_command *cmd, t_env_var **vars);

#endif
