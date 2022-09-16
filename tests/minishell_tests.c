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

/* Simple Command & global variables */
Test(minishell_tests, bin_ls, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls ../includes");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("builtins.h\nexecutor.h\nexpander.h\nparser.h\nstructs.h\ntokenizer.h\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/* Arguments & history */
Test(minishell_tests, bin_ls_l_t, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls -l -t ../includes");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("total 24\n-rw-r--r-- 1 root root 2126 Sep 16 07:45 builtins.h\n-rw-r--r-- 1 root root 1485 Sep 16 07:45 executor.h\n-rw-r--r-- 1 root root 1364 Sep 16 07:45 parser.h\n-rw-r--r-- 1 root root 1865 Sep 16 07:45 structs.h\n-rw-r--r-- 1 root root 1602 Sep  7 08:35 expander.h\n-rw-r--r-- 1 root root 1175 Sep  1 08:21 tokenizer.h\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, bin_ls_lt, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("/bin/ls -lt ../includes");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("total 24\n-rw-r--r-- 1 root root 2126 Sep 16 07:45 builtins.h\n-rw-r--r-- 1 root root 1485 Sep 16 07:45 executor.h\n-rw-r--r-- 1 root root 1364 Sep 16 07:45 parser.h\n-rw-r--r-- 1 root root 1865 Sep 16 07:45 structs.h\n-rw-r--r-- 1 root root 1602 Sep  7 08:35 expander.h\n-rw-r--r-- 1 root root 1175 Sep  1 08:21 tokenizer.h\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/* Echo */
Test(minishell_tests, echo_hello_world, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo Hello, World!");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("Hello, World!\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, echo_n_hello_world, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo -n Hello, World!");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("Hello, World!");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, echo, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, echo_n, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo -n");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, echo_$, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo $?");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("0\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/* Exit beetje iffy */
Test(minishell_tests, exit, .init=setup, .exit_code=0)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit");
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

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_42, .init=setup, .exit_code=42)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit 42");
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

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_hello, .init=setup, .exit_code=2)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit hello");
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

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_42_19, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit 42 19");
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

	cr_assert_stdout_eq_str("exit\nminishell: exit: too many arguments\n");

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_hello_world, .init=setup, .exit_code=2)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit hello world");
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

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_hello_42, .init=setup, .exit_code=2)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit hello 42");
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

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, exit_42_hello, .init=setup)
{
	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("exit 42 hello");
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

	cr_assert_stdout_eq_str("exit\nminishell: exit: too many arguments\n");

	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/* Return value of a process */
// Hebben we echo $? voor nodig

/* Signals */
// Moeten we nog bouwen

/* Double Quotes */
Test(minishell_tests, echo_double_quotes, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo \"cat lol.c | cat > lol.c\"");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("cat lol.c | cat > lol.c\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/* Single Quotes */
Test(minishell_tests, echo_$_user, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo \'$USER\'");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("$USER\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

Test(minishell_tests, echo_idan, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("echo \'hallo \'$PATH\' \'");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("hallo /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}

/* Env */
// is wel te schrijven

/* Export */
// is wel te schrijven

/* Unset */
// is wel te schrijven

/* Cd */
// is wel te schrijven

/* Pwd */
// is wel te schrijven

/* Relative path */
Test(minishell_tests, relative_path, .init=setup)
{
	char *user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	user_input = ft_strdup("../../usr/bin/ls ../includes");
	tokens = tokenizer(user_input);
	if (tokens == NULL)
	{
		free(user_input);
		free_tokens(tokens);
	}
	commands = parser(tokens);
	expander(commands, onze_env);
	executor(commands, &onze_env);

	cr_assert_stdout_eq_str("builtins.h\nexecutor.h\nexpander.h\nparser.h\nstructs.h\ntokenizer.h\n");
	free(user_input);
	free_tokens(tokens);
	free_commands(commands);
	free_env_vars(onze_env);
}


/* Environment path */
Test(minishell_tests, environment_path, .init=setup)
{
	unsigned int	i = 0;
	char			*user_inputs[4];

	user_inputs[0] = ft_strdup("unset PATH");
	user_inputs[1] = ft_strdup("export PATH=/bla/bla:/usr/bin");
	user_inputs[2] = ft_strdup("ls ../includes");
	user_inputs[3] = 0;


	char	*user_input;

	onze_env = environ_to_linked_list_recursive(onze_env, environ);
	while (user_inputs[i])
	{
		user_input = user_inputs[i];
		tokens = tokenizer(user_input);
		if (tokens == NULL)
		{
			free(user_input);
			free_tokens(tokens);
		}
		commands = parser(tokens);
		expander(commands, onze_env);
		executor(commands, &onze_env);

		free(user_input);
		free_tokens(tokens);
		free_commands(commands);

		i++;
	}	
	cr_assert_stdout_eq_str("builtins.h\nexecutor.h\nexpander.h\nparser.h\nstructs.h\ntokenizer.h\n");
	free_env_vars(onze_env);
}

/* Redirection */
// Verzin test samen met Idan

/* Pipes */


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
