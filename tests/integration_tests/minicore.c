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

void minicore(char **inputs, t_env_var *onze_env)
{
	t_command	*cmds;
	t_token		*tokens;
	char		*user_input;

	g_exit_status = 0;
	while (*inputs)
	{
		user_input = ft_strdup(*inputs);
		tokens = tokenizer(user_input);
		if (tokens == NULL)
		{
			free(user_input);
			free_tokens(tokens);

			inputs++;

			continue;
		}
		cmds = parser(tokens, &onze_env);
		expander(cmds, onze_env);
		if (cmds->cmd[0] == 0)
		{
			free(user_input);
			free_tokens(tokens);
			free_commands(cmds);

			inputs++;

			continue;
		}
		executor(cmds, &onze_env);
		add_history(user_input);
		free(user_input);
		free_tokens(tokens);
		free_commands(cmds);

		inputs++;
	}
	free_env_vars(onze_env);
}
