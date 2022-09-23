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

/* Environment path */
Test(minishell_tests, environment_path, .init=setup)
{
	unsigned int	i = 0;
	char			*user_inputs[4];

	user_inputs[0] = ft_strdup("unset PATH");
	user_inputs[1] = ft_strdup("export PATH=/bla/bla:/usr/bin");
	user_inputs[2] = ft_strdup("ls ../../includes");
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
	cr_assert_stdout_eq_str("builtins.h\nexecutor.h\nexpander.h\nminishell.h\nparser.h\nstructs.h\ntokenizer.h\n");
	free_env_vars(onze_env);
}
