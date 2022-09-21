#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../../includes/structs.h"
#include "../../includes/builtins.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/executor.h"
#include <readline/history.h>

extern char			**environ;
static t_command	*commands;
static t_token		*tokens;
static t_env_var	*onze_env;

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

/* Exit beetje iffy */
Test(minishell_tests, exit, .init=setup, .exit_code=0)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_42, .init=setup, .exit_code=42)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit 42");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_hello, .init=setup, .exit_code=2)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit hello");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_42_19, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit 42 19");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	cr_assert_stdout_eq_str("exit\nminishell: exit: too many arguments\n");

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_hello_world, .init=setup, .exit_code=2)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit hello world");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_hello_42, .init=setup, .exit_code=2)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit hello 42");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_42_hello, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit 42 hello");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	cr_assert_stdout_eq_str("exit\nminishell: exit: too many arguments\n");

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}
