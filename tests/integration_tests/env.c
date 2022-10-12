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

/* Env */
Test(minishell_tests, env, .init=setup)
{
	char *test_inputs[] = {
		"env",
		0
	};

	minicore(test_inputs, &onze_env);

	char	*a = two_d_to_str(environ);
	if (a == NULL)
	{
		perror("calloc");
		exit(1);
	}
	cr_assert_stdout_eq_str(a);
	free(a);
}
