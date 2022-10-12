/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/12 02:10:27 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

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

void	get_user_input(char **user_input)
{
	struct sigaction	sa;

	init_signals(&sa, &sigint_prompt_handler);
	*user_input = readline("minishell>");
	if (!(*user_input))
	{
		printf("exit\n");
		exit(0);
	}
	add_history(*user_input);
}

int	parser_and_expander(t_command **cmds, t_token *tokens,
				t_env_var **environ, char *user_input)
{
	*cmds = parser(tokens, environ);
	if (*cmds == NULL || (*cmds)->cmd == NULL)
	{
		if (*cmds)
			unlink((*cmds)->files->file_name);
		free(user_input);
		free_tokens(tokens);
		free_commands(*cmds);
		return (1);
	}
	expander(*cmds, *environ);
	if ((*cmds)->cmd[0] == 0)
	{
		free(user_input);
		free_tokens(tokens);
		free_commands(*cmds);
		return (1);
	}
	return (0);
}

static int	syntax_protector(t_token *token)
{
	if(!token)
		return (0);
	while (token)
	{
		if (token->type == REDIRECT_OP && (!token->next || token->next->type == WORD))
		{
			printf("Syntax error\n");
			return (0);
		}
		if (token->type == REDIRECT_OP && token->next && token->next->type != WORD)
		{
			printf("Syntax error\n");
			return (0);
		}
		if (token->type == PIPE && token->next && token->next->type == PIPE)
		{
			printf("Syntax error\n");
			return (0);
		}
		token = token->next;
	}
	return (1);
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
	minishell(environ);
	free_env_vars(environ);
	return (0);
}
