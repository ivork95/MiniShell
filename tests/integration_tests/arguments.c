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

/*
ls -i -S -r

-a = do not ignore entries starting with .
-i = print the index number of each file
-r = reverse order while sorting
-s = print the allocated size of each file, in blocks
-S = sort by file size, largest first
*/

/* Arguments & history */
Test(arguments, bin_ls_a_S, .init=setup)
{
	char *test_inputs[] = {
		"/bin/ls -a -S tests/example_folder/",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str(expected);
}

Test(arguments, bin_ls_aS, .init=setup)
{
	char *test_inputs[] = {
		"/bin/ls -aS tests/example_folder/",
		0
	};

	minicore(test_inputs, &onze_env);

	cr_assert_stdout_eq_str(expected);
}
