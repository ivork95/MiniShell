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

// void minicore(char **inputs, t_env_var *onze_env)
// {
// 	t_command	*cmds;
// 	t_token		*tokens;
// 	char		*user_input;

// 	g_exit_status = 0;
// 	while (*inputs)
// 	{
// 		user_input = ft_strdup(*inputs);
// 		tokens = tokenizer(user_input);
// 		if (tokens == NULL)
// 		{
// 			free(user_input);
// 			free_tokens(tokens);

// 			inputs++;

// 			continue;
// 		}
// 		cmds = parser(tokens, &onze_env);
// 		expander(cmds, onze_env);
// 		if (cmds->cmd[0] == 0)
// 		{
// 			free(user_input);
// 			free_tokens(tokens);
// 			free_commands(cmds);

// 			inputs++;

// 			continue;
// 		}
// 		executor(cmds, &onze_env);
// 		add_history(user_input);
// 		free(user_input);
// 		free_tokens(tokens);
// 		free_commands(cmds);

// 		inputs++;
// 	}
// 	free_env_vars(onze_env);
// }

static int	syntax_protector(t_token *token)
{
	if(!token)
		return (0);
	while (token)
	{
		if (token->type == REDIRECT_OP && (!token->next || token->next->type == WORD))
		{
			printf("Syntax error\n");
			return (0);
		}
		if (token->type == REDIRECT_OP && token->next && token->next->type != WORD)
		{
			printf("Syntax error\n");
			return (0);
		}
		if (token->type == PIPE && token->next && token->next->type == PIPE)
		{
			printf("Syntax error\n");
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	parser_and_expander(t_command **cmds, t_token *tokens,
				t_env_var **environ, char *user_input)
{
	*cmds = parser(tokens, environ);
	if (*cmds == NULL || (*cmds)->cmd == NULL)
	{
		if (*cmds)
			unlink((*cmds)->files->file_name);
		free(user_input);
		free_tokens(tokens);
		free_commands(*cmds);
		return (1);
	}
	expander(*cmds, *environ);
	if ((*cmds)->cmd[0] == 0)
	{
		free(user_input);
		free_tokens(tokens);
		free_commands(*cmds);
		return (1);
	}
	return (0);
}

void minicore(char **inputs, t_env_var *onze_env)
{
	t_command	*cmds;
	t_token		*tokens;
	char		*user_input;

	g_exit_status = 0;
	while (*inputs)
	{
		cmds = NULL;
		user_input = NULL;

		user_input = ft_strdup(*inputs);

		tokens = tokenizer(user_input);
		if (!syntax_protector(tokens))
		{
			free(user_input);
			free_tokens(tokens);

			inputs++;


			continue ;
		}
		if (parser_and_expander(&cmds, tokens, &onze_env, user_input))
		{
			inputs++;


			continue ;
		}
		executor(cmds, &onze_env);
		free(user_input);
		free_tokens(tokens);
		free_commands(cmds);

		inputs++;
	}
	free_env_vars(onze_env);
}
