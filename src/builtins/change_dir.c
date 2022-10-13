/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 16:11:41 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/13 15:04:54 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

static void	change_env_old_pwd(char *old_pwd, t_env_var **environ)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", old_pwd);
	if (env_var == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	add_env_var(environ, env_var);
	free(env_var);
}

static void	change_env_pwd(t_env_var **environ)
{
	char	*env_var;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env_var = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (env_var == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	add_env_var(environ, env_var);
	free(env_var);
}

static void	change_directory_inner(t_env_var **environ)
{
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	change_env_old_pwd(old_pwd, environ);
	free(old_pwd);
	change_env_pwd(environ);
}

static void	change_directory(t_command *command, t_env_var **environ)
{
	t_env_var	*home;

	if (command->args[1] == NULL)
	{
		home = find_env_var(*environ, "HOME");
		if (home == NULL)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_exit_status = 1;
			return ;
		}
		else if (chdir(home->value) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(home->value, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			g_exit_status = 1;
			return ;
		}
	}
	else if (chdir(command->args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(command->args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_exit_status = 1;
		return ;
	}
	change_directory_inner(environ);
	g_exit_status = 0;
}

void	cd_builtin(t_command *cmd, t_env_var **environ)
{
	size_t		i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("To many args\n", 2);
		return ;
	}
	change_directory(cmd, environ);
}
