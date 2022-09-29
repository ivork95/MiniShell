/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/29 17:52:43 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../includes/parser.h"
#include "../includes/expander.h"
#include "../includes/builtins.h"
#include "../includes/executor.h"
#include "../includes/signals.h"

int g_exit_status;

void	print_env(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->value, 1);
		head = head->next;
	}
}

void	minishell(t_env_var	*environ)
{
	t_command			*cmds;
	t_token				*tokens;
	char				*user_input;
	struct sigaction	sa;

	while (1)
	{
		init_signals(&sa, &sigint_prompt_handler);
		user_input = readline("minishel>");
		if (!user_input)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(user_input);
		tokens = tokenizer(user_input);
		if (tokens == NULL)
		{
			free(user_input);
			free_tokens(tokens);
			continue ;
		}
		cmds = parser(tokens, &environ);
		if (cmds == NULL || cmds->cmd == NULL)
		{
			free(user_input);
			free_tokens(tokens);
			continue ;
		}
		expander(cmds, environ);
		if (cmds->cmd[0] == 0)
		{
			free(user_input);
			free_tokens(tokens);
			free_commands(cmds);
			continue ;
		}
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
	minishell(environ);
	free_env_vars(environ);
	return (0);
}
