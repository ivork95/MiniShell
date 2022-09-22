/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:36:45 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/20 13:44:57 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../includes/expander.h"
#include "../libft/libft.h"

size_t	check_quote_type(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			return (SINGLE_QUOTES);
		else if (*str == '\"')
			return (DOUBLE_QUOTES);
		str++;
	}
	return (0);
}

size_t	get_len_place_holder(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || \
		(str[i] == 32) || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	return (i);
}

char	*get_env_value(char **envp, char *var, int var_len)
{
	char	*env_var;
	char	*empty;

	empty = "\0";
	while (*envp)
	{
		if (ft_strncmp(*envp, var, var_len) == 0)
		{
			env_var = ft_substr(*envp, var_len + 1, ft_strlen(*envp));
			ft_substr(*envp, var_len + 1, ft_strlen(*envp));
			free(var);
			return (env_var);
		}
		envp++;
	}
	return (empty);
}


size_t    is_expandable(char *str)
{
    char    *pos_dollar_sing;
    int     i;
    int     in_quotes;

    pos_dollar_sing = ft_strchr(str, '$');
    in_quotes = 0;
    i = 0;
    while (str[i])
    {
        if (str + i == pos_dollar_sing && !in_quotes)
            return (1);
        if (str[i] == '\'' && !in_quotes)
            in_quotes = 1;
        else if (str[i] == '\'')
            in_quotes = 0;
        i++;
    }
    return (0);
}


