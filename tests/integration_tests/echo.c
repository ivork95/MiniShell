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

/* Echo */
Test(echo, echo_hello_world, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);


	user_input = ft_strdup("echo Hello, World!");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);


	cr_assert_stdout_eq_str("Hello, World!\n");


	free_env_vars(onze_env);
}

Test(echo, echo_n_hello_world, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);


	user_input = ft_strdup("echo -n Hello, World!");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);


	cr_assert_stdout_eq_str("Hello, World!");


	free_env_vars(onze_env);
}

Test(echo, echo, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);


	user_input = ft_strdup("echo");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);


	cr_assert_stdout_eq_str("\n");


	free_env_vars(onze_env);
}

Test(echo, echo_n, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);


	user_input = ft_strdup("echo -n");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);


	cr_assert_stdout_eq_str("");


	free_env_vars(onze_env);
}

Test(echo, echo_$, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);


	user_input = ft_strdup("echo $?");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);


	cr_assert_stdout_eq_str("0\n");


	free_env_vars(onze_env);
}