/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_old.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/06/24 19:54:34 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../../includes/parser.h"


t_llnode *create_new_node()
{
	t_llnode *new;
	
	new = malloc(sizeof(t_llnode));
		if (new == NULL)
		exit(EXIT_FAILURE);
	new->next = NULL;
	return (new);
}

void	add_list_front(t_llnode **head, t_llnode *new_node)
{
	new_node->next = *head;
	*head = new_node;
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
	t_llnode	*new_node;

	(*str_dup)++;
	start = *str_dup;
	end = find_closing_quote(str_dup, delimiter);
	
	new_node = create_new_node();
	new_node->str = malloc(end - start + 1);
	if (new_node->str == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_node->str, start, end - start + 1);
	add_list_front(head, new_node);
	
	print_arguments(start, end - start);

}

void	handle_spaces(char **str_dup, t_llnode **head)
{
	char		*start;
	char		*end;
	t_llnode	*new_node;

	start = *str_dup;
	end = find_end_word(str_dup);

	new_node = create_new_node();
	new_node->str = malloc(end - start + 1);
	if (new_node->str == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_node->str, start, end - start + 1);
	add_list_front(head, new_node);
	
	print_arguments(start, end - start);
}

t_llnode	*split_words(char *str)
{
	t_llnode *head;

	head = create_new_node();
	char	*str_dup;

	str_dup = str;
	while (*str_dup != '\0')
	{
		if (*str_dup == '\'')
			handle_quotes(&str_dup, &head, '\'');
		if (*str_dup == '\"')
			handle_quotes(&str_dup, &head, '\"');
		if (*str_dup != ' ')
			handle_spaces(&str_dup, &head);
		str_dup++;
	}
	return (head);
}


void free_linked_list(t_llnode *head)
{
	t_llnode *tmp;
	
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

void print_list(t_llnode *head)
{
	while (head->next != NULL)
	{
		printf("|%s|\n", head->str);
		head = head->next;
	}
}

// t_llnode	*parser(char *str)
// {
// 	// char	*str = "\'ls \' \"-la\" grep '|' \"wc\" -l ";

// 	t_llnode *head;

// 	head = create_new_node();

// 	// printf("before = %p\n", head);
// 	head = split_words(str);
// 	// printf("after = %p\n", head);


// 	print_list(head);
// 	free_linked_list(head);
// 	return (head);
// }

int	main(void)
{
	char	*str = "\'ls \' \"-la\" grep '|' \"wc\" -l ";

	t_llnode *head;

	// head = create_new_node();

	// printf("before = %p\n", head);
	head = split_words(str);
	// printf("after = %p\n", head);


	print_list(head);
	free_linked_list(head);
	return (0);
}
