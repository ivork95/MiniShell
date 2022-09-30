/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_envp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:11:26 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/30 16:11:36 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*expand_envp(char *str, char *pos_dollar_sign, t_env_var *envp)
{
	t_expand_data	data;

	null_data(&data);
	data = set_data(data, str, pos_dollar_sign, envp);
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
	free_expand_data(&data);
	free(str);
	return (data.new_str);
}
