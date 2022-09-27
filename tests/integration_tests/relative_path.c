#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "minicore.h"

extern char			**environ;
static t_env_var	*onze_env;

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
	onze_env = environ_to_linked_list_recursive(onze_env, environ);
}

/* Relative path */
Test(minishell_tests, relative_path, .init=setup)
{
	char *inputs[] = {
		"../usr/bin/ls tests/example_folder",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("0\nempty_directory\nfile\nrandom.c\n");
}
