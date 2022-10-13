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

/* Exit beetje iffy */
Test(exit, exit, .init=setup, .exit_code=0)
{
	char *test_inputs[] = {
		"exit",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_42, .init=setup, .exit_code=42)
{
	char *test_inputs[] = {
		"exit 42",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_overflow, .init=setup, .exit_code=2)
{
	char *test_inputs[] = {
		"exit 999999999999999999999999999999999999999999999999",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_300, .init=setup, .exit_code=44)
{
	char *test_inputs[] = {
		"exit 300",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_minus_300, .init=setup, .exit_code=212)
{
	char *test_inputs[] = {
		"exit -300",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_hello, .init=setup, .exit_code=2)
{
	char *test_inputs[] = {
		"exit hello",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_42_19, .init=setup)
{
	char *test_inputs[] = {
		"exit 42 19",
		"echo $?",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stderr_eq_str("exit\nminishell: exit: too many arguments\n");
	cr_assert_stdout_eq_str("1\n");
}

Test(exit, exit_hello_world, .init=setup, .exit_code=2)
{
	char *test_inputs[] = {
		"exit hello world",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_hello_42, .init=setup, .exit_code=2)
{
	char *test_inputs[] = {
		"exit hello 42",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(exit, exit_42_hello, .init=setup)
{
	char *test_inputs[] = {
		"exit 42 hello",
		"echo $?",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stderr_eq_str("exit\nminishell: exit: too many arguments\n");
	cr_assert_stdout_eq_str("1\n");
}

Test(exit, exit_42_pipe_exit_a, .init=setup)
{
	char *test_inputs[] = {
		"exit 42 | exit a",
		"echo $?",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("2\n");
}

Test(exit, exit_a, .init=setup, .exit_code=2)
{
	char *test_inputs[] = {
		"exit a",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("2\n");
}
