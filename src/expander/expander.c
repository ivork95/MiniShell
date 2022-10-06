/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/25 03:05:34 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/06 15:08:59 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*expand_envp(char *str, char *pos_dollar_sign, t_env_var *envp)
{
	t_expand_data	data;

	null_data(&data);
	data = set_data(data, str, pos_dollar_sign, envp);
	if (data.len == 0)
	{
		free_expand_data(&data);
		return (str);
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

static int	set_mode(char c, int mode)
{
	if (c == '\"' && mode == 0)
		return (2);
	else if (c == '\"' && mode == 2)
		return (0);
	else if (c == '\'' && mode == 0)
		return (1);
	else if (c == '\'' && mode == 1)
		return (0);
	return (mode);
}

static void	expand_args_inner(char **arg, int i, t_env_var *envp)
{
	char	*dup;

	dup = ft_strdup(*arg);
	*arg = expand_envp(*arg, *arg + i, envp);
	if (ft_strncmp(dup, *arg, ft_strlen(dup) + 1))
		i = 0;
	else
		i += 1;
	free(dup);
	expand_args(arg, i, envp);
}

void	expand_args(char **arg, int start, t_env_var *envp)
{
	size_t	i;
	size_t	mode;

	i = 0 + start;
	mode = 0;
	while ((*arg)[i])
	{
		mode = set_mode((*arg)[i], mode);
		if ((*arg)[i] == '$' && mode != 1)
		{
			if (ft_strlen(*arg + i) == 1)
				break ;
			if (ft_strncmp(*arg + i, "$?", 2) == 0)
			{
				*arg = expand_exit_code(*arg, *arg + i);
				continue ;
			}
			expand_args_inner(arg, i, envp);
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
		expand_args(&commands->args[i], 0, envp);
		remove_quotes(&commands->args[i], start);
		if (i == 0)
			commands->cmd = commands->args[i];
		i++;
	}
	commands->cmd = commands->args[0];
}
