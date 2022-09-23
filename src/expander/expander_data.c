/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 17:51:48 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/23 12:05:26 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	null_data(t_expand_data *data)
{
	data->env_name = NULL;
	data->env_str = NULL;
	data->first_part_str = NULL;
	data->joined_str = NULL;
	data->last_part_str = NULL;
	data->pos_dollar_sign = NULL;
}

t_expand_data	set_data(t_expand_data data, char *str)
{
	data.len = get_len_place_holder(data.pos_dollar_sign + 1);
	data.env_name = ft_substr(data.pos_dollar_sign, 1, data.len);
	if (data.env_name == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.first_part_str = ft_substr(str, 0, data.pos_dollar_sign - str);
	if (data.first_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.last_part_str = ft_substr(data.pos_dollar_sign, data.len + 1,
			ft_strlen(data.pos_dollar_sign));
	if (data.last_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	return (data);
}

void	free_expand_data(t_expand_data *data)
{
	free(data->env_name);
	free(data->first_part_str);
	free(data->joined_str);
	free(data->last_part_str);
}
