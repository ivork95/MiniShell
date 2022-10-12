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

/* Single Quotes */
Test(single_quotes, echo_$_user, .init=setup)
{
	char *test_inputs[] = {
		"echo \'$USER\'",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("$USER\n");
}

Test(single_quotes, echo_idan_zonder_backslash, .init=setup)
{
	char *test_inputs[] = {
		"echo 'hallo '$PATH' '",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str("hallo /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin \n");
}
