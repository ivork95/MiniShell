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

/* Simple Command & global variables */
Test(simple_command, bin_ls, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls tests/example_folder/");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("0\nempty_directory\nrandom.c\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}
