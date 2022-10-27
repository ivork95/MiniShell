/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_dir_cont.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 15:00:00 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/27 15:21:00 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

int	cd_old_pwd(t_env_var *environ)
{
	t_env_var	*old_pwd;

	old_pwd = find_env_var(environ, "OLDPWD");
	if (old_pwd == NULL)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		g_exit_status = 1;
		return (1);
	}
	else if (chdir(old_pwd->value) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(old_pwd->value, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	print_error(char *cmd, char *old_pwd)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	free(old_pwd);
}
