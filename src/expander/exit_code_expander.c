/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_code_expander.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:36:45 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 20:25:10 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

extern int	g_exit_status;

static t_expand_data	get_exit_code(t_expand_data data, char *str,
			char *pos_dollar)
{
	data.len = 1;
	data.env_str = ft_itoa(g_exit_status);
	if (data.env_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.first_part_str = ft_substr(str, 0, pos_dollar - str);
	if (data.first_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.last_part_str = ft_substr(pos_dollar, data.len + 1,
			ft_strlen(pos_dollar));
	if (data.last_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	return (data);
}

char	*expand_exit_code(char *str, char *pos_dollar_sign)
{
	t_expand_data	data;

	null_data(&data);
	data = get_exit_code(data, str, pos_dollar_sign);
	if (data.last_part_str[0] && data.first_part_str[0])
	{
		data.joined_str = ft_strjoin(data.first_part_str, data.env_str);
		data.new_str = ft_strjoin(data.joined_str, data.last_part_str);
	}
	else if (data.first_part_str[0])
		data.new_str = ft_strjoin(data.first_part_str, data.env_str);
	else if (data.last_part_str[0])
		data.new_str = ft_strjoin(data.env_str, data.last_part_str);
	else
		data.new_str = ft_strdup(data.env_str);
	free(data.env_str);
	free_expand_data(&data);
	free(str);
	return (data.new_str);
}
