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
static char			*expected = "total 8\n-rw-r--r-- 1 root root 34 Sep 26 07:43 random.c\ndrwxr-xr-x 2 root root 64 Sep 26 07:42 empty_directory\n-rw-r--r-- 1 root root 19 Sep 26 07:42 0\n";

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

/* Arguments & history */
Test(arguments, bin_ls_l_t, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls -l -t tests/example_folder/");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str(expected);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(arguments, bin_ls_lt, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls -lt tests/example_folder/");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str(expected);
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}
