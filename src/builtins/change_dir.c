/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 16:11:41 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/01 13:09:16 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include <unistd.h>
#include <stdio.h>

void	change_directory(t_command *cmd, t_env_var **environ)
{
	char	*old_pwd;
	char	*env_var;

	old_pwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		if (chdir(getenv("HOME")) == -1)
		{
			ft_putendl_fd("error\n", 2);
			return ;
		}
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		ft_putendl_fd("error\n", 2);
		return ;
	}
	env_var = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (env_var = NULL)
		exit(EXIT_FAILURE);
	add_env_var(environ, env_var);
	free(env_var);
}
