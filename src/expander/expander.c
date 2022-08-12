/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 02:05:30 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/12 13:16:33 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"

size_t check_quote_type(char *str)
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

char	*remove_quotes(char *str, char delimiter)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_str;
	
	len  = count_letters(str, delimiter);
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
	printf("new str = %s\n", new_str);
	return (new_str);
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

size_t get_len_place_holder(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32) || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	return (i);
}

size_t is_expandable(char *str, char *position_dollar_sign)
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

char *expand_envp(char *str, char **envp)
{
	t_expand_data data;

	data.position_dollar_sign = ft_strchr(str, '$');

	if (is_expandable(str, data.position_dollar_sign))
	{
		data.len = get_len_place_holder(data.position_dollar_sign + 1);
		data.env_name = ft_substr(data.position_dollar_sign, 1, data.len);
		printf("env_name = %s\nlen = %ld\n", data.env_name, data.len);

		data.first_part_str = ft_substr(str, 0, data.position_dollar_sign - str);
		printf("first part of str = ::%s::\n", data.first_part_str);
		data.last_part_str = ft_substr(data.position_dollar_sign, data.len + 1, ft_strlen(data.position_dollar_sign));
		printf("last part of str = ::%s::\n", data.last_part_str);

		printf("env_name = %s\n", data.env_name);
		data.env_str = get_env_value(envp, data.env_name, data.len);
		printf("env_str = %s\n", data.env_str);


		if (data.last_part_str[0] && data.first_part_str[0])
		{
			data.joined_str = ft_strjoin(data.first_part_str, data.env_str);
			printf("join str = ::%s::\n", data.joined_str);
			data.new_str = ft_strjoin(data.joined_str, data.last_part_str);
			free(data.joined_str);
			// return ()
		}

		else if (data.first_part_str[0])
		{
			printf("str = %s\n", str);
			data.new_str = ft_strjoin(data.first_part_str, data.env_str);
			printf("joined = %s\n", data.new_str);
		}
		else if (data.last_part_str[0])
		{
			data.new_str = ft_strjoin(data.env_str, data.last_part_str);
		}
		else
		{
			data.new_str = data.env_str;
		}
		return (data.new_str);
		//free env_name;
		//free first part
		//free last part
		//free env_str
		//free data.joined_str
		//free str

	
		// if (data.last_part_str[0] && data.first_part_str[0])
		// 	return (ft_strjoin(data.new_str, data.last_part_str));
		// else if (data.first_part_str[0])
		// 	return (data.new_str);
		// else if (data.last_part_str)
		// 	return (ft_strjoin(data.env_str, data.last_part_str));
		// else
		// 	return (data.env_str);
	}
	return (str);
}

void    expand_command(t_command *command, char **envp)
{
	size_t quote_type;

		command->cmd = expand_envp(command->cmd, envp);
		// quote_type = check_quote_type(command->cmd);
		// if (quote_type == SINGLE_QUOTES)
		// {
		// 	command->cmd = remove_quotes(command->cmd, '\'');
		// 	command->args[0] = command->cmd;
		// 	return ;
		// }
		// else if (quote_type == DOUBLE_QUOTES)
		// {
		// 	command->cmd = remove_quotes(command->cmd, '\"');
			
		// }

}

void    expand_args(t_command *command, char **envp)
{
	size_t i;
	size_t quote_type;

	i = 0;
	while(command->args[i])
	{
		quote_type = check_quote_type(command->args[i]);
		if (quote_type == SINGLE_QUOTES)
		{
			command->args[i] = remove_quotes(command->args[i], '\'');
		}
		// else if (quote_type == DOUBLE_QUOTES)
		
		i++;
	}
}

void    expander(t_command *commands, char **envp)
{
	// t_command *tmp;

	// tmp = commands;
	expand_command(commands, envp);
	// expand_args(commands, envp);
	// while (tmp)
	// {
	//     expand_args(commands, envp);
	//     tmp = tmp->next;
	// }
	// return (commands);
}