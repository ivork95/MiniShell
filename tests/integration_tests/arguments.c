#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../../includes/structs.h"
#include "../../includes/builtins.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/executor.h"
#include <readline/history.h>

extern char			**environ;
static t_command	*commands;
static t_token		*tokens;
static t_env_var	*onze_env;

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

/* Arguments & history */
Test(arguments, bin_ls_l_t, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls -l -t  ../../includes/");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("total 28\n-rw-r--r-- 1 root root  145 Sep 23 11:58 minishell.h\n-rw-r--r-- 1 root root 1857 Sep 23 11:57 executor.h\n-rw-r--r-- 1 root root 2173 Sep 23 11:57 builtins.h\n-rw-r--r-- 1 root root 1586 Sep 23 11:56 expander.h\n-rw-r--r-- 1 root root 1198 Sep 23 10:19 tokenizer.h\n-rw-r--r-- 1 root root 1433 Sep 23 09:53 parser.h\n-rw-r--r-- 1 root root 1845 Sep 22 12:11 structs.h\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(arguments, bin_ls_lt, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls -lt ../../includes/");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("total 28\n-rw-r--r-- 1 root root  145 Sep 23 11:58 minishell.h\n-rw-r--r-- 1 root root 1857 Sep 23 11:57 executor.h\n-rw-r--r-- 1 root root 2173 Sep 23 11:57 builtins.h\n-rw-r--r-- 1 root root 1586 Sep 23 11:56 expander.h\n-rw-r--r-- 1 root root 1198 Sep 23 10:19 tokenizer.h\n-rw-r--r-- 1 root root 1433 Sep 23 09:53 parser.h\n-rw-r--r-- 1 root root 1845 Sep 22 12:11 structs.h\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}
