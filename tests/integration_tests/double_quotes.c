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

/* Double Quotes */
Test(minishell_tests, echo_double_quotes, .init=setup)
{
	char *test_inputs[] = {
		"echo \"cat lol.c | cat > lol.c\"",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("cat lol.c | cat > lol.c\n");
}
