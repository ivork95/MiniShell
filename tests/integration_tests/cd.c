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
static char			*expected = "0\nempty_directory\nrandom.c\n";

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

/* Cd */
Test(cd, cd, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);


	user_input = ft_strdup("cd");
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


	user_input = ft_strdup("/bin/ls");
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

Test(cd, cd_parent, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("cd ..");
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


	user_input = ft_strdup("/bin/ls pwd/tests/example_folder");
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

	cr_assert_stdout_eq_str(expected);

	free_env_vars(onze_env);
}

Test(cd, cd_current, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("cd .");
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


	user_input = ft_strdup("/bin/ls tests/example_folder");
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

	cr_assert_stdout_eq_str(expected);

	free_env_vars(onze_env);
}

Test(cd, cd_wrong, .init=setup)
{
	char *user_input;
	onze_env = environ_to_linked_list_recursive(onze_env, environ);

	user_input = ft_strdup("cd blabla");
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

	cr_assert_stderr_eq_str("minishell: chdir: No such file or directory\n");

	free_env_vars(onze_env);
}
