#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/tokenizer.h"
#include "../includes/parser.h"
#include "../includes/builtins.h"

extern char	**environ;

static void	print_env(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->value, 1);
		head = head->next;
	}
}

static void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

static void	setup(void)
{
	redirect_all_std();
}

Test(exit, without_args, .init=setup)
{
	char	*input_str = "exit";
	char	*expected = "exit\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

Test(exit, with_numeric_arg, .init=setup)
{
	char	*input_str = "exit 42";
	char	*expected = "exit\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

Test(exit, with_non_numeric_arg, .init=setup)
{
	char	*input_str = "exit hello";
	char	*expected = "exit\nminishell: exit: hello: numeric argument required\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

Test(exit, with_multiple_numeric_args, .init=setup)
{
	char	*input_str = "exit 42 19";
	char	*expected = "exit\nminishell: exit: too many arguments\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

Test(exit, with_multiple_non_numeric_args, .init=setup)
{
	char	*input_str = "exit hello world";
	char	*expected = "exit\nminishell: exit: hello: numeric argument required\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

Test(exit, with_nonn_numerical_mixed, .init=setup)
{
	char	*input_str = "exit hello 42";
	char	*expected = "exit\nminishell: exit: hello: numeric argument required\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

Test(exit, with_numerical_nonn_mixed, .init=setup)
{
	char	*input_str = "exit 42 hello";
	char	*expected = "exit\nminishell: exit: too many arguments\n";

	t_token *tokens = tokenizer(input_str);
	t_command *commands = parser(tokens);
	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

	exit_builtin(commands, &ll_environ);
	cr_assert_stdout_eq_str(expected);
}

/*
gcc \
exit_tests.c \
-lcriterion \
../src/parser/parser.c \
../src/parser/parser_utils.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
../src/builtins/env.c \
../src/builtins/export.c \
../src/builtins/unset.c \
../src/builtins/change_dir.c \
../src/builtins/echo.c \
../src/builtins/pwd.c \
../src/builtins/exit.c \
-L../src/libft -l:libft.a
*/