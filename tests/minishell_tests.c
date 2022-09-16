#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/structs.h"
#include "../includes/builtins.h"
#include "../includes/tokenizer.h"
#include "../includes/parser.h"
#include "../includes/expander.h"
#include "../includes/executor.h"
#include <readline/history.h>

extern char	**environ;
t_command	*commands;
t_token		*tokens;
t_env_var	*onze_env;

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

Test(minishell_tests, echo_hello_pipe_cat, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo hello | cat");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);
	add_history(user_input);

	cr_assert_stdout_eq_str("hello\n");

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, bin_ls, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("a.out\ncd_tests.c\necho_tests.c\nexecve_tests.c\nexit_tests.c\nexpander_tests.c\nexport_tests.c\nminishell_tests.c\nparser_tests.c\ntest_cmds\ntokenizer_tests.c\nunset_tests.c\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/*
gcc \
minishell_tests.c \
-lcriterion \
../src/builtins/echo.c \
../src/builtins/pwd.c \
../src/builtins/change_dir.c \
../src/builtins/env.c \
../src/builtins/export.c \
../src/builtins/unset.c \
../src/builtins/exit.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
../src/parser/parser.c \
../src/parser/parser_utils.c \
../src/expander/expander.c \
../src/expander/expander_data.c \
../src/expander/expander_utils.c \
../src/executor/executor.c \
../src/executor/executor_utils.c \
../src/executor/processes.c \
../src/parser/free_breezy.c \
-lreadline \
-L../src/libft -l:libft.a
*/
