/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 22:00:12 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/08 13:32:52 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

t_token	*create_new_token(void)
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

t_token	*tokenize_special_opp(char *str)
{
	t_token	*token;

	token = create_new_token();
	if (*str == '|')
	{
		token->str = str;
		token->type = PIPE;
		token->len = 1;
	}
	else if (*str == '<' || *str == '>')
	{
		token->str = str;
		token->type = REDIRECT_OP;
		if (*(str + 1) == *str)
			token->len = 2;
		else
			token->len = 1;
	}
	return (token);
}

/* " "he'        llo" */
t_token	*tokenize_word(char *str)
{
	t_token		*new_token;
	size_t		len;
	int			quote;

	new_token = create_new_token();
	quote = 0;
	len = 0;
	while ((str[len] && quote) || (str[len] != '\0'
			&& !ft_isspace(str[len]) && !isspecialchar(str[len])))
	{
		if ((str[len] == '\'' || str[len] == '\"') && quote == 0)
		{
			quote = str[len];
			new_token->quoted = true;
		}
		else if (str[len] == quote)
			quote = 0;
		len++;
	}
	new_token->type = WORD;
	new_token->str = str;
	new_token->len = len;
	return (new_token);
}

t_token	*tokenizer(char *str)
{
	t_token	*token;

	while (ft_isspace(*str))
		str++;
	if (!(*str))
		return (NULL);
	if (isspecialchar(*str))
	{
		token = tokenize_special_opp(str);
		token->next = tokenizer(str + token->len);
		return (token);
	}
	token = tokenize_word(str);
	if (str[token->len] != '\0')
		token->next = tokenizer(str + token->len);
	return (token);
}
