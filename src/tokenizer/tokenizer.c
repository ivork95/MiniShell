#include "../../includes/minishell.h"
#include "../libft/libft.h"
#include <ctype.h>
#include <stdio.h>

t_tokens *tokenizer(char *str)
{

	t_tokens *token;
	size_t len;
	int quote;

	len = 0;
	while (*str == ' ') 
		str++;
	token = malloc(sizeof(t_tokens));
	quote = 0;

	if (*str == '|')
	{
		token->str = str;
		token->type = PIPE;
		token->len = 1;
	}

	while ((str[len] && quote) || (str[len] != '\0' && !isspace(str[len]) && str[len] != '<' && str[len] != '>' && str[len] != '|'))
	{
		token->type = WORD;
		if ((str[len] == '\'' || str[len] == '\"') && quote == 0)
		{
			quote = str[len];
			token->quoted = true;
		}
		else if (str[len] == quote)
			quote = 0;
		len++;
	}
	if (token->type == WORD)
	{
		token->str = str;
		token->len = len;
	}
	else
		len += token->len;
	if (str[len] != '\0')
		token->next = tokenizer(str + len);
	else
		token->next = NULL;
	return (token);
}

void	print_list(t_tokens *head)
{
	while (head != NULL)
	{
		printf("|%s|\n", head->str);
		head = head->next;
	}
}

int main(void)
{
	char *s = "\'helloo\'   world|test    this \"string   \"        forme";
	t_tokens *list;


	printf("test before tokenizer\n");
	list = tokenizer(s);
	printf("test after tokenizer\n");
	print_list(list);
	return (0);
}
