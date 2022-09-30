/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:36:45 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 11:25:10 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/*
** TODO check the official end of env var string
*/
size_t	get_len_place_holder(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalnum(str[i]) && str[i] != '?' )
			break ;
		i++;
	}
	return (i);
}

void	null_data(t_expand_data *data)
{
	data->env_name = NULL;
	data->env_str = NULL;
	data->first_part_str = NULL;
	data->joined_str = NULL;
	data->last_part_str = NULL;
}

t_expand_data	set_data(t_expand_data data, char *str, char *pos_dollar_sign,
			t_env_var *envp)
{
	data.len = get_len_place_holder(pos_dollar_sign + 1);
	data.env_name = ft_substr(pos_dollar_sign, 1, data.len);
	if (data.env_name == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.first_part_str = ft_substr(str, 0, pos_dollar_sign - str);
	if (data.first_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.last_part_str = ft_substr(pos_dollar_sign, data.len + 1,
			ft_strlen(pos_dollar_sign));
	if (data.last_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	if (find_env_var(envp, data.env_name))
		data.env_str = find_env_var(envp, data.env_name)->value;
	else
		data.env_str = "\0";
	return (data);
}

void	free_expand_data(t_expand_data *data)
{
	free(data->env_name);
	free(data->first_part_str);
	free(data->joined_str);
	free(data->last_part_str);
}
