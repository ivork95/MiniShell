/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/14 22:00:12 by ivork         #+#    #+#                 */
/*   Updated: 2022/07/14 22:16:44 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../libft/libft.h"
#include <ctype.h>
#include <stdio.h>

size_t	isspecialchar(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

t_tokens	*create_new_node(void)
{
	t_tokens	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->str = NULL;
	new->next = NULL;
	return (new);
}

t_tokens	*tokenize_special_opp(char *str)
{
	t_tokens	*token;

	token = create_new_node();
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

t_tokens	*tokenize_word(char *str)
{
	t_tokens	*token;
	size_t		len;
	int			quote;

	token = create_new_node();
	quote = 0;
	len = 0;
	while ((str[len] && quote) || (str[len] != '\0'
			&& !isspace(str[len]) && !isspecialchar(str[len])))
	{
		if ((str[len] == '\'' || str[len] == '\"') && quote == 0)
		{
			quote = str[len];
			token->quoted = true;
		}
		else if (str[len] == quote)
			quote = 0;
		len++;
	}
	token->type = WORD;
	token->str = str;
	token->len = len;
	return (token);
}

t_tokens	*tokenizer(char *str)
{
	t_tokens	*token;

	while (*str == ' ')
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

void	print_list(t_tokens *head)
{
	while (head != NULL)
	{
		printf("$%s$\n", head->str);
		head = head->next;
	}
}

int	main(void)
{
	char		*s = "\'helloo\'   world|test  ||   this \"string   \"        \"forme\"<outfile>>       \"quotes > not | closed  ";
	t_tokens	*list;

	list = tokenizer(s);
	print_list(list);
	return (0);
}
