/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/06/24 16:58:56 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef struct s_llnode
{
	char			*str;
	struct s_llnode	*next;
}	t_llnode;

void	*insert(t_llnode **head, char *start, char *end)
{
	t_llnode	*next;

	next = malloc(sizeof(*next));
	if (next == NULL)
		exit(EXIT_FAILURE);
	next->str = malloc(end - start + 1);
	if (next->str == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(next->str, start, end - start + 1);
	next->next = *head;
	*head = next;
}

void	print_arguments(char *str, long int length)
{
	int	i;

	i = 0;
	printf("|");
	while (length > i)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("|\n");
}

char	*find_closing_quote(char **str_dup, char delimiter)
{
	char	*end;

	end = NULL;
	while (**str_dup != '\0')
	{
		if (**str_dup == delimiter)
		{
			end = *str_dup;
			(*str_dup)++;
			break ;
		}
		(*str_dup)++;
	}
	return (end);
}

char	*find_end_word(char **str_dup)
{
	char	*end;

	end = NULL;
	while (**str_dup != '\0')
	{
		if (**str_dup == ' ')
			return (*str_dup);
		(*str_dup)++;
	}
	end = (*str_dup)--;
	return (end);
}

void	handle_quotes(char **str_dup, t_llnode **head, char delimiter)
{
	char		*start;
	char		*end;
	t_llnode	*next;

	(*str_dup)++;
	start = *str_dup;
	end = find_closing_quote(str_dup, delimiter);
	print_arguments(start, end - start);
	insert(head, start, end);
}

void	handle_spaces(char **str_dup, t_llnode **head)
{
	char		*start;
	char		*end;
	t_llnode	*next;

	start = *str_dup;
	end = find_end_word(str_dup);
	print_arguments(start, end - start);
	insert(head, start, end);
}

void	beta(t_llnode **head, char *str)
{
	char	*str_dup;

	str_dup = str;
	while (*str_dup != '\0')
	{
		if (*str_dup == '\'')
			handle_quotes(&str_dup, head, '\'');
		if (*str_dup == '\"')
			handle_quotes(&str_dup, head, '\"');
		if (*str_dup != ' ')
			handle_spaces(&str_dup, head);
		str_dup++;
	}
}

int	main(void)
{
	char	*str = "\'ls \' \"-la\" grep";

	t_llnode *head;
	head = malloc(sizeof(*head));
	if (head == NULL)
		exit(EXIT_FAILURE);
	head->next = NULL;

	printf("before = %p\n", head);
	beta(&head, str);
	printf("after = %p\n", head);

	while (head->next != NULL)
	{
		printf("|%s|\n", head->str);
		head = head->next;
	}
}
