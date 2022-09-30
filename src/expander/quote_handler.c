/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 20:02:34 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 20:25:30 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static char	*copy_string_without_quotes(char *str, char *first, char *next)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 2 + 1));
	if (new_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str + i != next && str + i != first)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_quotes(char **str, int start)
{
	int		i;
	char	*next_occurance;
	char	*first_occurance;
	char	*new_str;

	i = 0 + start;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			first_occurance = (*str) + i;
			next_occurance = ft_strchr(*str + i + 1, (*str)[i]);
			new_str = copy_string_without_quotes(
					*str, first_occurance, next_occurance);
			i = next_occurance - *str - 1;
			free(*str);
			*str = new_str;
			remove_quotes(str, i);
			return ;
		}
		i++;
	}
	return ;
}
