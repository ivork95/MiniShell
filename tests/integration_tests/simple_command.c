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

/* Simple Command & global variables */
Test(simple_command, bin_ls, .init=setup)
{
	char *test_inputs[] = {
		"/bin/ls tests/example_folder/",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("0\nempty_directory\nfile\nrandom.c\n");
}

Test(simple_command, double_quotes_only, .init=setup)
{
	char *test_inputs[] = {
		"\"\"",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("minishell: \"\": command not found");
}

Test(simple_command, empty_string, .init=setup)
{
	char *test_inputs[] = {
		"",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("");
}

Test(simple_command, space, .init=setup)
{
	char *test_inputs[] = {
		" ",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("");
}

Test(simple_command, spaces, .init=setup)
{
	char *test_inputs[] = {
		"                 ",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("");
}

Test(simple_command, outer_quote_not_closed, .init=setup, .exit_code=1)
{
	char *test_inputs[] = {
		"echo ' hallo", // echo ' hallo
		0
	};

	minicore(test_inputs, &onze_env);
}

Test(simple_command, inner_quote_not_closed, .init=setup)
{
	char *test_inputs[] = {
		"echo \"hallo' \"", // echo "hallo' "
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("hallo' \n");
}

Test(simple_command, outer_quote_not_closed_2, .init=setup, .exit_code=1)
{
	char *test_inputs[] = {
		"echo \"hallo' \" teest 'this' string'", // echo "hallo' " teest 'this' string'
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(simple_command, heredoc_without_delim_cmd, .init=setup)
{
	char *test_inputs[] = {
		"<<",
		"echo $?",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("minishell: syntax error\n2\n");
}
