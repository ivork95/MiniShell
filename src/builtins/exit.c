/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:28:45 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/08 16:40:58 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

bool	str_is_numeric(char *s)
{
	if (ft_strlen(s) == ft_strlen(ft_itoa(ft_atoi(s))))
		return (true);
	return (false);
}

void	handle_exit_multiple_args(char **cmd_args, pid_t cpid)
{
	if (!str_is_numeric(cmd_args[1]))
	{
		if (cpid != 0)
			ft_putendl_fd("exit", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
		ft_putstr_fd(cmd_args[1], STDOUT_FILENO);
		ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
		exit(2);
	}
	else
	{
		if (cmd_args[2] == NULL)
		{
			if (cpid != 0)
				ft_putendl_fd("exit", STDOUT_FILENO);
			exit(ft_atoi(cmd_args[1]));
		}
		else
		{
			if (cpid != 0)
				ft_putendl_fd("exit\n", STDOUT_FILENO);
			ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
		}
	}
}

void	exit_builtin(t_command *cmd, t_env_var **vars)
{
	unsigned int	argc;

	argc = 1;
	while (cmd->args[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		if (cmd->cpid != 0)
			ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (argc > 1)
		handle_exit_multiple_args(cmd->args, cmd->cpid);
}
