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
#include <string.h>
#include <stdlib.h>

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
	;
	redirect_all_std();
}

static char *two_d_to_str(void)
{
	unsigned int	i = 0;
	unsigned int	j = 0;
	size_t			s = 0;

	// Tel hoeveel characters gemalloced moeten worden
	while (environ[i])
	{
		s = s + strlen(environ[i]) + 1;
		i++;
	}

	// Zet 2d array om in string
	char			*a = malloc(s);
	char			*a_dup = a;
	i = 0;
	while (environ[i])
	{
		strncpy(a_dup, environ[i], strlen(environ[i]));
		a_dup = a_dup + strlen(environ[i]);
		a_dup[0] = '\n';
		a_dup++;
		i++;
	}
	a_dup[0] = '\0';
	return (a);
}

/* Env */
Test(minishell_tests, unset, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("unset HOSTNAME");
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

	user_input = ft_strdup("env");
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

	unsetenv("HOSTNAME");
	cr_assert_stdout_eq_str(two_d_to_str());

	free_env_vars(onze_env);
}

Test(minishell_tests, unset_multiple, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("unset HOSTNAME PWD");
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

	user_input = ft_strdup("env");
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

	unsetenv("HOSTNAME");
	unsetenv("PWD");
	cr_assert_stdout_eq_str(two_d_to_str());

	free_env_vars(onze_env);
}

Test(minishell_tests, unset_empty, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("unset");
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

	user_input = ft_strdup("env");
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

	unsetenv("");
	cr_assert_stdout_eq_str(two_d_to_str());

	free_env_vars(onze_env);
}

Test(minishell_tests, unset_nonexist, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("unset bestaatniet");
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

	user_input = ft_strdup("env");
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

	unsetenv("bestaatniet");
	cr_assert_stdout_eq_str(two_d_to_str());

	free_env_vars(onze_env);
}