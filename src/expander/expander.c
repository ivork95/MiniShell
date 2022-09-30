/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/25 03:05:34 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 18:54:36 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

extern int g_exit_status;

char	*copy_string_without_quotes(char *str, char *first, char *next)
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

static void	remove_quotes(char **str, int start)
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

char	*expand_envp(char *str, char *pos_dollar_sign, t_env_var *envp)
{
	t_expand_data	data;

	null_data(&data);
	data = set_data(data, str, pos_dollar_sign, envp);
	if (data.len == 0)
	{
		free_expand_data(&data);
		return(str);
	}
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

t_expand_data	set_exit_code(t_expand_data data, char *str, char *pos_dollar_sign)
{
	data.len = 1;
	data.env_str = ft_itoa(g_exit_status);
	if (data.env_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.first_part_str = ft_substr(str, 0, pos_dollar_sign - str);
	if (data.first_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	data.last_part_str = ft_substr(pos_dollar_sign, data.len + 1,
			ft_strlen(pos_dollar_sign));
	if (data.last_part_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	return (data);
}

char	*expand_exit_code(char *str, char *pos_dollar_sign)
{
	t_expand_data	data;

	null_data(&data);
	data = set_exit_code(data, str, pos_dollar_sign);
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

static void	expand_args(char **arg, t_env_var *envp, int start)
{
	size_t	i;
	size_t	mode;

	i = 0 + start;
	mode = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\"' && mode == 0)
			mode = 2;
		else if ((*arg)[i] == '\"' && mode == 2)
			mode = 0;
		else if ((*arg)[i] == '\'' && mode == 0)
			mode = 1;
		else if ((*arg)[i] == '\'' && mode == 1)
			mode = 0;
		if ((*arg)[i] == '$' && mode != 1)
		{
			if (ft_strlen(*arg + i) == 1)
				break ;
			if (ft_strncmp(*arg + i, "$?", 2) == 0)
			{
				*arg = expand_exit_code(*arg, *arg + i);
				continue;
			}
			char *dup = ft_strdup(*arg);
			*arg = expand_envp(*arg, *arg + i, envp);
			if (ft_strncmp(dup, *arg, ft_strlen(dup) + 1))
				i = 0;
			else
				i += 1;
			free(dup);
			expand_args(arg, envp, i);
			return ;
		}
		i++;
	}
}

void	expander(t_command *commands, t_env_var *envp)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (commands->args[i])
	{
		expand_args(&commands->args[i], envp, 0);
		remove_quotes(&commands->args[i], start);
		if (i == 0)
			commands->cmd = commands->args[i];
		i++;
	}
	commands->cmd = commands->args[0];
}
