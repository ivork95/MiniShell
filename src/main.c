/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/11/15 16:00:24 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

void	print_env(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(head->value, STDOUT_FILENO);
		head = head->next;
	}
}

int	increment_shlvl(t_env_var **environ)
{
	t_env_var	*shlvl;
	int			current_shlvl;

	shlvl = find_env_var(*environ, "SHLVL");
	if (shlvl && str_is_numeric(shlvl->value))
	{
		current_shlvl = ft_atoi(shlvl->value);
		if (current_shlvl < 1)
		{
			add_env_var(environ, "SHLVL=1");
			return (1);
		}
		current_shlvl++;
		free(shlvl->value);
		shlvl->value = ft_itoa(current_shlvl);
		return (0);
	}
	add_env_var(environ, "SHLVL=1");
	return (1);
}

static void	get_user_input(char **user_input)
{
	struct sigaction	sa;

	init_signals(&sa, &sigint_prompt_handler);
	*user_input = readline("minishell>");
	if (!(*user_input))
	{
		ft_putendl_fd("exit", 2);
		exit(g_exit_status);
	}
}

void	minishell(t_env_var	*environ)
{
	t_command			*cmds;
	t_token				*tokens;
	char				*user_input;

	while (1)
	{
		cmds = NULL;
		user_input = NULL;
		get_user_input(&user_input);
		tokens = tokenizer(user_input);
		if (!syntax_protector(tokens))
		{
			free(user_input);
			free_tokens(tokens);
			continue ;
		}
		add_history(user_input);
		if (parser_and_expander(&cmds, tokens, &environ, user_input))
			continue ;
		executor(cmds, &environ);
		free(user_input);
		free_tokens(tokens);
		free_commands(cmds);
	}
	free_env_vars(environ);
}

int	main(int argc, char **const argv, char **envp)
{
	t_env_var	*environ;

	g_exit_status = 0;
	(void)argc;
	(void)argv;
	environ = NULL;
	environ = environ_to_linked_list_recursive(environ, envp);
	increment_shlvl(&environ);
	minishell(environ);
	free_env_vars(environ);
	return (0);
}
