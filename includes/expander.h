/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:02:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 16:28:15 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* Private libraries */
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

/* Public libraries */
# include "parser.h"
# include "builtins.h"
# include "structs.h"
# include "../src/libft/libft.h"
# include "minishell.h"

# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

/* expand_args.c */
void			expand_args(char **arg, t_env_var *envp);

/* expand_envp.c */
char			*expand_envp(char *str, char *pos_dollar_sign, t_env_var *envp);

/* expand_utils.c */
size_t			get_len_place_holder(char *str);
void			null_data(t_expand_data *data);
t_expand_data	set_data(t_expand_data data, char *str, char *pos_dollar_sign,
					t_env_var *envp);
void			free_expand_data(t_expand_data *data);

/* expander.c */
char			*expand_exit_code(char *str, char *pos_dollar_sign,
					t_env_var *envp);
void			expander(t_command *commands, t_env_var *envp);

#endif
