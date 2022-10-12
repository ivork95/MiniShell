#include "minicore.h"

int g_exit_status;

char	*two_d_to_str(char **environ)
{
	unsigned int	i = 0;
	unsigned int	j = 0;
	size_t			s = 0;
	char			*a;
	char			*a_dup;

	while (environ[i])
	{
		s = s + strlen(environ[i]);
		i++;
	}
	s = s + i + 1;
	a = calloc(s, sizeof(*a));
	if (a == NULL)
	{
		perror("calloc");
		exit(1);
	}
	a_dup = a;
	i = 0;
	while (environ[i])
	{
		strncpy(a_dup, environ[i], strlen(environ[i]));
		a_dup = a_dup + strlen(environ[i]);
		*a_dup = '\n';
		a_dup++;
		i++;
	}
	return (a);
}

static void	get_user_input(char **user_input)
{
	struct sigaction	sa;

	init_signals(&sa, &sigint_prompt_handler);
	*user_input = ft_strdup(*user_input);
	if (!(*user_input))
	{
		printf("exit\n");
		exit(0);
	}
	add_history(*user_input);
}

void minicore(char **test_inputs, t_env_var *onze_env)
{
	t_command	*cmds;
	t_token		*tokens;
	char		*user_input;

	g_exit_status = 0;
	while (*test_inputs)
	{
		cmds = NULL;
		user_input = NULL;
		user_input = *test_inputs;
		get_user_input(&user_input);
		tokens = tokenizer(user_input);
		// if (!syntax_protector(tokens))
		if (tokens == NULL)
		{
			free(user_input);
			free_tokens(tokens);

			test_inputs++;

			continue;
		}
		if (parser_and_expander(&cmds, tokens, &onze_env, user_input))
		{
			test_inputs++;

			continue ;
		}

		executor(cmds, &onze_env);
		free(user_input);
		free_tokens(tokens);
		free_commands(cmds);

		test_inputs++;
	}
	free_env_vars(onze_env);
}
