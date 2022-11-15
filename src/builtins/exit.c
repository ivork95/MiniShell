/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:28:45 by kawish        #+#    #+#                 */
/*   Updated: 2022/11/15 15:59:35 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

bool	str_is_numeric(char *s)
{
	char			*ascii;
	unsigned int	i;

	i = 0;
	if (*s == '-')
		s++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	ascii = ft_itoa(ft_atoi(s));
	if (ascii == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	if (ft_strlen(s) != ft_strlen(ascii))
	{
		free(ascii);
		return (false);
	}
	free(ascii);
	return (true);
}

static void	handle_exit_multiple_args(char **cmd_args, pid_t cpid)
{
	if (!str_is_numeric(cmd_args[1]))
	{
		if (cpid != 0)
			ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd_args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	else
	{
		if (cmd_args[2] == NULL)
		{
			if (cpid != 0)
				ft_putendl_fd("exit", STDERR_FILENO);
			exit(ft_atoi(cmd_args[1]) % 256);
		}
		else
		{
			if (cpid != 0)
				ft_putendl_fd("exit", STDERR_FILENO);
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			g_exit_status = 1;
		}
	}
}

void	exit_builtin(t_command *cmd, t_env_var **vars)
{
	unsigned int	argc;

	(void)vars;
	argc = 1;
	while (cmd->args[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		if (cmd->cpid != 0)
			ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (argc > 1)
		handle_exit_multiple_args(cmd->args, cmd->cpid);
}
