/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/13 12:51:15 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/parser.h"
#include "../includes/expander.h"
#include "../includes/builtins.h"
#include "../includes/executor.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*commands;
	t_token		*tokens;
	t_env_var	*environ;
	char		*user_input;

	environ = NULL;
	environ = environ_to_linked_list_recursive(environ, envp);
	while (1)
	{
		user_input = readline(">");
		tokens = tokenizer(user_input);
		if (tokens == NULL)
		{
			free(user_input);
			free_tokens(tokens);
			continue;
		}
		commands = parser(tokens);
		expander(commands, environ);
		executor(commands, &environ);
		add_history(user_input);
		free(user_input);
		free_tokens(tokens);
		free_commands(commands);
	}
	free_env_vars(environ);
	return (0);
}
