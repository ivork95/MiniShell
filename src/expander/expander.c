/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 02:05:30 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 12:48:47 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../includes/expander.h"
#include "../libft/libft.h"

char	*remove_quotes(char *str, char delimiter)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_str;

	len = count_letters(str, delimiter);
	new_str = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	return (new_str);
}

char	*expand_envp(char *str, char **envp)
{
	t_expand_data	data;

	data.pos_dollar_sign = ft_strchr(str, '$');
	if (data.pos_dollar_sign)
	{
		data.len = get_len_place_holder(data.pos_dollar_sign + 1);
		data.env_name = ft_substr(data.pos_dollar_sign, 1, data.len);
		data.first_part_str = ft_substr(str, 0, data.pos_dollar_sign - str);
		data.last_part_str = ft_substr(data.pos_dollar_sign, data.len + 1, \
		ft_strlen(data.pos_dollar_sign));
		data.env_str = get_env_value(envp, data.env_name, data.len);
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
			data.new_str = data.env_str;
		return (data.new_str);
	}
	return (str);
}

void	expand_command(t_command *command, char **envp)
{
	size_t	quote_type;

	quote_type = check_quote_type(command->cmd);
	if (quote_type == SINGLE_QUOTES)
	{
		command->cmd = remove_quotes(command->cmd, '\'');
	}
	if (quote_type == DOUBLE_QUOTES)
	{
		command->cmd = remove_quotes(command->cmd, '\"');
		command->cmd = expand_envp(command->cmd, envp);
	}
	else
		command->cmd = expand_envp(command->cmd, envp);
	command->args[0] = command->cmd;
}

void	expand_args(t_command *command, char **envp)
{
	size_t	i;
	size_t	quote_type;

	i = 1;
	while (command->args[i])
	{
		quote_type = check_quote_type(command->args[i]);
		if (quote_type == SINGLE_QUOTES)
		{
			command->args[i] = remove_quotes(command->args[i], '\'');
		}
		else if (quote_type == DOUBLE_QUOTES)
		{
			command->args[i] = expand_envp(command->args[i], envp);
			command->args[i] = remove_quotes(command->args[i], '\"');
		}
		else
			command->args[i] = expand_envp(command->args[i], envp);
		i++;
	}
}

void	expander(t_command *commands, char **envp)
{
	expand_command(commands, envp);
	expand_args(commands, envp);
}
