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

/* Pipes */
Test(pipes, echo_pipe_echo, .init=setup)
{
	char *test_inputs[] = {
		"echo | echo",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("\n");
}

Test(pipes, pipes, .init=setup)
{
	char *test_inputs[] = {
		"cat tests/example_folder/file | grep bla | more",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("bla\nbla\n");
}
