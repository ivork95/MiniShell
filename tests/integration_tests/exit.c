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
	char *inputs[] = {
		"exit",
		0
	};

	minicore(inputs, onze_env);
}

Test(exit, exit_42, .init=setup, .exit_code=42)
{
	char *inputs[] = {
		"exit 42",
		0
	};

	minicore(inputs, onze_env);
}

Test(exit, exit_hello, .init=setup, .exit_code=2)
{
	char *inputs[] = {
		"exit hello",
		0
	};

	minicore(inputs, onze_env);
}

Test(exit, exit_42_19, .init=setup)
{
	char *inputs[] = {
		"exit 42 19",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("exit\nminishell: exit: too many arguments\n");
}

Test(exit, exit_hello_world, .init=setup, .exit_code=2)
{
	char *inputs[] = {
		"exit hello world",
		0
	};

	minicore(inputs, onze_env);
}

Test(exit, exit_hello_42, .init=setup, .exit_code=2)
{
	char *inputs[] = {
		"exit hello 42",
		0
	};

	minicore(inputs, onze_env);
}

Test(exit, exit_42_hello, .init=setup)
{

	char *inputs[] = {
		"exit 42 hello",
		0
	};

	minicore(inputs, onze_env);

	cr_assert_stdout_eq_str("exit\nminishell: exit: too many arguments\n");
}
