/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/05 17:16:06 by kawish        ########   odam.nl         */
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

void	err_func(char *str, int code)
{
	perror(str);
	exit(code);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	return ;
}

char	*get_path(char **arguments, char *cmd)
{
	char	*path;
	char	*full_path;
	int		i;

	while (*arguments)
	{
		if (ft_strncmp(*arguments, "PATH=", 5) == 0)
			path = ft_strdup(*arguments);
		arguments++;
	}
	arguments = ft_split(path, ':');
	free(path);
	i = 0;
	path = ft_strjoin("/", cmd);
	while (arguments[i])
	{
		full_path = ft_strjoin(arguments[i], path);
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		i++;
	}
	free_array(arguments);
	free(path);
	return (full_path);
}

void	execute_command(t_command *cmd, t_env_var **head)
{
	size_t i;

	i = 0;
	while (lookup_table[i].builtin_name)
	{
		if (!ft_strncmp(cmd->cmd, lookup_table[i].builtin_name, ft_strlen(cmd->cmd)))	
			lookup_table[i].function(cmd, head);
		i++;
	}
}

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

int	main(int argc, char **const argv, char **envp)
{
	t_command	*cmds;
	t_token		*tokens;
	t_env_var	*environ;
	char		*user_input;

	environ = environ_to_linked_list_recursive(environ, envp);
	while (1)
	{
		user_input = readline(">");
		tokens = tokenizer(user_input);
		// print_tokens(tokens);
		cmds = parser(tokens);
		expander(cmds, environ);
		execute_command(cmds, &environ);
		add_history(user_input);
		free(user_input);
		free_tokens(tokens);
		free_commands(cmds);
	}
	free_env_vars(environ);
	return (0);
}
