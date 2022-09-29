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
	char *inputs[] = {
		"/bin/ls tests/example_folder/",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("0\nempty_directory\nfile\nrandom.c\n");
}

Test(simple_command, double_quotes_only, .init=setup)
{
	char *inputs[] = {
		"\"\"",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("minishell: \"\": command not found");
}

Test(simple_command, empty_string, .init=setup)
{
	char *inputs[] = {
		"",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("");
}

Test(simple_command, space, .init=setup)
{
	char *inputs[] = {
		" ",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("");
}

Test(simple_command, spaces, .init=setup)
{
	char *inputs[] = {
		"                 ",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("");
}

// Test(simple_command, quote_not_closed, .init=setup)
// {
// 	char *inputs[] = {
// 		"echo ' hallo",
// 		0
// 	};

// 	printf("input str = %s\n", inputs[0]);
// 	minicore(inputs, onze_env);

// 	cr_assert_stdout_eq_str("");
// }

// Test(simple_command, quote_not_closed_2, .init=setup)
// {
// 	char *inputs[] = {
// 		"echo \"hallo' \"",
// 		0
// 	};

// 	printf("input str = %s\n", inputs[0]);
// 	minicore(inputs, onze_env);

// 	cr_assert_stdout_eq_str("");
// }

// Test(simple_command, quote_not_closed_3, .init=setup)
// {
// 	char *inputs[] = {
// 		"echo \"hallo' \" teest 'this' string'",
// 		0
// 	};

// 	printf("input str = %s\n", inputs[0]);
// 	minicore(inputs, onze_env);

// 	cr_assert_stdout_eq_str("");
// }
