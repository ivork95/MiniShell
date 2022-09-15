/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 02:05:30 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/15 20:54:24 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*remove_quotes(char *str, char delimiter)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*last_occurence;
	char	*first_occurence;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
	if (new_str == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	last_occurence = ft_strrchr(str, delimiter);
	first_occurence = ft_strchr(str, delimiter);
	while (str[i])
	{
		if (str + i != last_occurence && str + i != first_occurence)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*expand_envp(char *str, t_env_var *envp)
{
	t_expand_data	data;
	//needs refactor
	null_data(&data);
	data.pos_dollar_sign = ft_strchr(str, '$');
	if (data.pos_dollar_sign)
	{
		if (ft_strlen(data.pos_dollar_sign) == 1)
			return (str);
		data = set_data(data, str);
		if (find_env_var(envp, data.env_name))
			data.env_str = find_env_var(envp, data.env_name)->value;
		else
			data.env_str = ft_strdup("\0");
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
		return (data.new_str);
	}
	return (str);
}

void	expand_command(t_command *command, t_env_var *envp)
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

void	expand_args(t_command *command, t_env_var *envp)
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

void	expander(t_command *commands, t_env_var *envp)
{
	expand_command(commands, envp);
	expand_args(commands, envp);
}
