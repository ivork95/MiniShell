/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/25 03:05:34 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/12 02:03:55 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

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

static bool	check_if_exists(char *str, t_env_var *envp)
{
	char	*s;

	if (!ft_isdigit(str[1]) && !ft_isalnum(str[1]) && str[1] != '?')
		return (true);
	s = ft_strchr(str + 1, '$');
	if (!s)
		s = ft_substr(str, 1, strlen(str));
	else
		s = ft_substr(str, 1, s - str);
	if (!find_env_var(envp, s))
	{
		free(s);
		return (false);
	}
	free(s);
	return (true);
}

static void	expand_args_inner(char **arg, int i, t_env_var *envp)
{
	char	*dup;

	dup = ft_strdup(*arg);
	*arg = expand_envp(*arg, *arg + i, envp);
	if ((*arg)[i] == '\0' || !check_if_exists(dup + i, envp))
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
