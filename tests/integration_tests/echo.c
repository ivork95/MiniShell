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

/* Echo */
Test(echo, echo_hello_world, .init=setup)
{
	char *test_inputs[] = {
		"echo Hello, World!",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("Hello, World!\n");
}

Test(echo, echo_n_hello_world, .init=setup)
{
	char *test_inputs[] = {
		"echo -n Hello, World!",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("Hello, World!");
}

Test(echo, echo, .init=setup)
{
	char *test_inputs[] = {
		"echo",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("\n");
}

Test(echo, echo_n, .init=setup)
{
	char *test_inputs[] = {
		"echo -n",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("");
}

Test(echo, echo_$_question_mark, .init=setup)
{
	char *test_inputs[] = {
		"echo $?",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("0\n");
}

Test(echo, echo_$, .init=setup)
{
	char *test_inputs[] = {
		"echo $",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("$\n");
}

Test(echo, echo_$$, .init=setup)
{
	char *test_inputs[] = {
		"echo $$",
		0
	};
	minicore(test_inputs, onze_env);
	cr_assert_stdout_eq_str("Should echo current PID\n");
}
