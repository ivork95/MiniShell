/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 22:00:12 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/09 19:29:10 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

t_token	*malloc_new_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(*new_token));
	if (new_token == NULL)
		exit(EXIT_FAILURE);
	new_token->str = NULL;
	new_token->quoted = false;
	new_token->next = NULL;
	new_token->quoted = false;
	new_token->len = 0;
	new_token->type = 0;
	return (new_token);
}

t_token	*tokenize_special_opp(char *user_input)
{
	t_token	*token;

	token = malloc_new_token();
	if (*user_input == '|')
	{
		token->str = user_input;
		token->type = PIPE;
		token->len = 1;
	}
	else if (*user_input == '<' || *user_input == '>')
	{
		token->str = user_input;
		token->type = REDIRECT_OP;
		if (*(user_input + 1) == *user_input)
			token->len = 2;
		else
			token->len = 1;
	}
	return (token);
}

/* " "he'        llo" */
t_token	*tokenize_word(char *user_input)
{
	t_token		*token;
	size_t		len;
	int			quote;

	token = malloc_new_token();
	quote = 0;
	len = 0;
	while ((user_input[len] && quote) || (user_input[len] != '\0'
			&& !ft_isspace(user_input[len]) && !isspecialchar(user_input[len])))
	{
		if ((user_input[len] == '\'' || user_input[len] == '\"') && quote == 0)
		{
			quote = user_input[len];
			token->quoted = true;
		}
		else if (user_input[len] == quote)
			quote = 0;
		len++;
	}
	token->type = WORD;
	token->str = user_input;
	token->len = len;
	return (token);
}

t_token	*tokenizer(char *user_input)
{
	t_token	*token;

	while (ft_isspace(*user_input))
		user_input++;
	if (!(*user_input))
		return (NULL);
	if (isspecialchar(*user_input))
	{
		token = tokenize_special_opp(user_input);
		token->next = tokenizer(user_input + token->len);
		return (token);
	}
	token = tokenize_word(user_input);
	if (user_input[token->len] != '\0')
		token->next = tokenizer(user_input + token->len);
	return (token);
}
