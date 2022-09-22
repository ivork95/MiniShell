/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 14:02:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/22 14:12:17 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "builtins.h"
# include "structs.h"
# include "../src/libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

void			expander(t_command *commands, t_env_var *envp);
size_t			is_expandable(char *str);
size_t			get_len_place_holder(char *str);
size_t			count_letters(char *str, char delimiter);
size_t			check_quote_type(char *str);
char			*get_env_value(char **envp, char *var, int var_len);
void			null_data(t_expand_data *data);
t_expand_data	set_data(t_expand_data data, char *str);
void			free_expand_data(t_expand_data *data);
#endif