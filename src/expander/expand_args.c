/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:09:47 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/30 16:10:32 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	expand_args(char **arg, t_env_var *envp)
{
	size_t	i;
	size_t	mode;

	i = 0;
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
				*arg = expand_exit_code(*arg, *arg + i, envp);
				continue ;
			}
			*arg = expand_envp(*arg, *arg + i, envp);
			expand_args(arg, envp);
			return ;
		}
		i++;
	}
}
