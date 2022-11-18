/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 16:11:41 by ivork         #+#    #+#                 */
/*   Updated: 2022/11/18 12:54:49 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

static void	change_env_old_pwd(char *old_pwd, t_env_var **environ)
{
	char	*env_var;

	env_var = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
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

static int	cd_home(t_env_var *environ)
{
	t_env_var	*home;

	home = find_env_var(environ, "HOME");
	if (home == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_exit_status = 1;
		return (1);
	}
	else if (chdir(home->value) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home->value, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static void	change_directory(t_command *command, t_env_var **environ)
{
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (command->args[1] == NULL || *(command->args[1]) == '\0'
		|| !ft_strncmp(command->args[1], "~", 2))
	{
		if (cd_home(*environ))
			return (free(old_pwd));
	}
	else if (ft_strncmp(command->args[1], "-", 2) == 0)
	{
		if (cd_old_pwd(*environ))
			return (free(old_pwd));
	}
	else if (chdir(command->args[1]) == -1)
	{
		print_error(command->args[1], old_pwd);
		g_exit_status = 1;
		return ;
	}
	if (old_pwd)
		change_env_old_pwd(old_pwd, environ);
	change_env_pwd(environ);
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
		ft_putendl_fd("To many args", 2);
		g_exit_status = 1;
		return ;
	}
	change_directory(cmd, environ);
}
