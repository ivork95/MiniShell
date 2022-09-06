#include "../../includes/builtins.h"

void		exit_builtin(t_command *cmd, t_env_var **vars)
{
	unsigned int	argc;
	int				exit_status;

	argc = 1;
	while (cmd->args[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		exit_status = ft_atoi(cmd->args[1]);
		if (ft_strlen(cmd->args[1]) == ft_strlen(ft_itoa(exit_status))) 
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(exit_status);
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
			exit(2);
		}
	}
	else
	{
		exit_status = ft_atoi(cmd->args[1]);
		if (ft_strlen(cmd->args[1]) == ft_strlen(ft_itoa(exit_status))) 
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
			exit(2);
		}
	}
}