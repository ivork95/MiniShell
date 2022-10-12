#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "minicore.h"

extern char			**environ;
static t_env_var	*onze_env;
static char			*expected = "..\n.\nempty_directory\nrandom.c\nfile\n0\n";

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

Test(expander, double_envp, .init = setup)
{
	char *test_inputs[] = {
		"echo $HOME$HOME",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("/root/root\n");
}

Test(expander, envp_with_dollar, .init = setup)
{
	char *test_inputs[] = {
		"echo $HOME$",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("/root$\n");
}

Test(expander, sandwichde_quotes, .init = setup)
{
	char *test_inputs[] = {
		"e'ch'o \"hell\"o world",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("hello world\n");
}

Test(expander, single_quotes_inside_double, .init = setup)
{
	char *test_inputs[] = {
		"e'ch'o \"hello '$HOME'\"",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("hello '/root'\n");
}

Test(expander, double_quotes_inside_double, .init = setup)
{
	char *test_inputs[] = {
		"echo \"hello \"$HOME\"\"",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("hello /root\n");
}

Test(expander, linked_expanstion, .init = setup)
{
	char *test_inputs[] = {
		"echo test$HOME",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("test/root\n");
}

Test(expander, linked_expanstion_rev, .init = setup)
{
	char *test_inputs[] = {
		"echo $HOMEtest",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("\n");
}

Test(expander, double_quotes_remove, .init = setup)
{
	char *test_inputs[] = {
		"echo \"hello\"$HOME\"bye\"",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("hello/rootbye\n");
}

Test(expander, multiple_quotes_inside, .init = setup)
{
	char *test_inputs[] = {
		"echo \"hello 'test' 'this' 'string' bye\"",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("hello 'test' 'this' 'string' bye\n");
}

Test(expander, ikweetniet, .init = setup)
{
	char *test_inputs[] = {
		"echo $TEST$PWD",
		0
	};
	minicore(test_inputs, &onze_env);
	cr_assert_stdout_eq_str("/pwd\n");
}
