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
Test(export, export_jon_aegon, .init=setup, .disabled=true)
{
	char *test_inputs[] = {
		"export jon=aegon",
		0
	};

	minicore(test_inputs, &onze_env);

	char	*a = two_d_to_str(environ);
	if (a == NULL)
	{
		perror("calloc");
		exit(1);
	}
	setenv("jon", "aegon", 1);
	cr_assert_stdout_eq_str(a);
	free(a);
}

Test(export, export_hostname, .init=setup, .disabled=true)
{
	char *test_inputs[] = {
		"export HOSTNAME=EWAA",
		0
	};

	minicore(test_inputs, &onze_env);

	char	*a = two_d_to_str(environ);
	if (a == NULL)
	{
		perror("calloc");
		exit(1);
	}
	setenv("HOSTNAME", "EWAA", 1);
	cr_assert_stdout_eq_str(a);
	free(a);
}

Test(export, export_oswin, .init=setup)
{
	char *test_inputs[] = {
		"export VAR='$BAR'",
		"export BAR='$VAR'",
		"echo $VAR",
		0
	};
	minicore(test_inputs, &onze_env);
}

Test(export, export_substr, .init=setup)
{
	char *test_inputs[] = {
		"export HOS=FOUT",
		0
	};
	minicore(test_inputs, &onze_env);

	cr_assert_not_null(find_env_var(onze_env, "HOSTNAME"));
}

Test(export, export_plus_equals, .init=setup)
{
	char *test_inputs[] = {
		"export kawish=gangster",
		"export kawish+=flikkertje",
		0
	};
	minicore(test_inputs, &onze_env);

	t_env_var *x = find_env_var(onze_env, "kawish");
	cr_assert_not_null(x);
	if (x)
		cr_assert(eq(str, "gangsterflikkertje", x->value));
}

Test(export, export_plus_equals_twee, .init=setup)
{
	char *test_inputs[] = {
		"export kawish+=gangster",
		0
	};
	minicore(test_inputs, &onze_env);

	t_env_var *x = find_env_var(onze_env, "kawish");
	cr_assert_not_null(x);
	if (x)
		cr_assert(eq(str, "gangster", x->value));
}

Test(export, export_key_with_equals, .init=setup)
{
	char *test_inputs[] = {
		"export kawish=",
		0
	};
	minicore(test_inputs, &onze_env);

	t_env_var *x = find_env_var(onze_env, "kawish");
	cr_assert_not_null(x);
	if (x)
		cr_assert(eq(str, "kawish", x->key));
		cr_assert(eq(str, "", x->value));
}

Test(export, export_key_only, .init=setup)
{
	char *test_inputs[] = {
		"export kawish",
		0
	};
	minicore(test_inputs, &onze_env);

	t_env_var *x = find_env_var(onze_env, "kawish");
	cr_assert_not_null(x);
	if (x)
		cr_assert(zero(ptr, x->value));
}