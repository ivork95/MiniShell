/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:36:45 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 12:49:03 by ivork         ########   odam.nl         */
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

size_t	count_letters(char *str, char delimiter)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != delimiter)
		i++;
	return (i);
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
	char	*full_path;

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

size_t	is_expandable(char *str, char *position_dollar_sign)
{
	bool	expandable;
	size_t	i;

	if (!position_dollar_sign)
		return (false);
	expandable = true;
	while (*str != *position_dollar_sign)
	{
		if (*str == '\'' && expandable == true)
			expandable = false;
		else if (*str == '\'')
			expandable = true;
		str++;
	}
	return (expandable);
}
