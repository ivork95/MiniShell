/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:02:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/06 15:07:58 by kgajadie      ########   odam.nl         */
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

/* exit_code_expander.c */
char			*expand_exit_code(char *str, char *pos_dollar_sign);

/* expander_data.c */
t_expand_data	set_data(t_expand_data data, char *str, char *pos_dollar_sign,
					t_env_var *envp);
void			null_data(t_expand_data *data);
void			free_expand_data(t_expand_data *data);

/* quote_handler.c */
void			remove_quotes(char **str, int start);

/* expander.c */
void			expander(t_command *commands, t_env_var *envp);
void			expand_args(char **arg, int start, t_env_var *envp);
char			*expand_envp(char *str, char *pos_dollar_sign, t_env_var *envp);

#endif
