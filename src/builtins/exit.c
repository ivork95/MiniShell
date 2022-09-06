#include "../../includes/builtins.h"

bool	str_is_numeric(char *s)
{
	if (ft_strlen(s) == ft_strlen(ft_itoa(ft_atoi(s))))
		return (true);
	return (false);
}

void	handle_exit_multiple_args(char **cmd_args)
{
	if (!str_is_numeric(cmd_args[1])) // Eerste argument is geen valid numerical
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		printf("minishell: exit: %s: numeric argument required\n", cmd_args[1]);
		exit(2);
	}
	else
	{
		if (cmd_args[2] == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(ft_atoi(cmd_args[1]));
		}
		else
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
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
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else if (argc > 1) // Input is meer dan alleen "echo"
	{
		handle_exit_multiple_args(cmd->args);
		// if (!str_is_numeric(cmd->args[1])) // Eerste argument is geen valid numerical
		// {
		// 	ft_putendl_fd("exit", STDOUT_FILENO);
		// 	printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
		// 	exit(2);
		// }
		// else
		// {
		// 	if (cmd->args[2] == NULL)
		// 	{
		// 		ft_putendl_fd("exit", STDOUT_FILENO);
		// 		exit(ft_atoi(cmd->args[1]));
		// 	}
		// 	else
		// 	{
		// 		ft_putendl_fd("exit", STDOUT_FILENO);
		// 		ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
		// 	}
		// }
	}

	// else if (argc > 1)
	// {
	// 	exit_status = ft_atoi(cmd->args[1]);
	// 	if (ft_strlen(cmd->args[1]) != ft_strlen(ft_itoa(exit_status)))
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
	// 		exit(2);
	// 	}
	// 	if (ft_strlen(cmd->args[1]) == ft_strlen(ft_itoa(exit_status)) && cmd->args[2] == NULL)
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		exit(exit_status);
	// 	}
	// 	else if (ft_strlen(cmd->args[1]) == ft_strlen(ft_itoa(exit_status)) && cmd->args[2] != NULL)
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
	// 	}
	// }


	// else if (argc == 2)
	// {
	// 	exit_status = ft_atoi(cmd->args[1]);
	// 	if (ft_strlen(cmd->args[1]) == ft_strlen(ft_itoa(exit_status))) 
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		exit(exit_status);
	// 	}
	// 	else
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
	// 		exit(2);
	// 	}
	// }
	// else
	// {
	// 	exit_status = ft_atoi(cmd->args[1]);
	// 	if (ft_strlen(cmd->args[1]) == ft_strlen(ft_itoa(exit_status))) 
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
	// 	}
	// 	else
	// 	{
	// 		ft_putendl_fd("exit", STDOUT_FILENO);
	// 		printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
	// 		exit(2);
	// 	}
	// }
}