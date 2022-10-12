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

/* Return value of a process */
Test(return_value, return_value_error, .init=setup)
{
	char *test_inputs[] = {
		"ls ./bestaatniet",
		"echo $?",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stderr_eq_str("ls: cannot access './bestaatniet': No such file or directory\n");
	cr_assert_stdout_eq_str("2\n");
}

Test(return_value, return_value, .init=setup)
{
	char *test_inputs[] = {
		"ls tests/example_folder/",
		"echo $?",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("0\nempty_directory\nfile\nrandom.c\n0\n");
}

Test(return_value, return_value_een, .init=setup)
{
	char *test_inputs[] = {
		"bestaatniet",
		"echo $?",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("minishell: bestaatniet: command not found\n127\n");
}
