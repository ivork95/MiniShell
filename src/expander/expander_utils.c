/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:36:45 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/23 12:03:41 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

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

size_t	is_expandable(char *str)
{
	char	*pos_dollar_sing;
	int		i;
	int		in_quotes;

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
