/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/07/07 18:30:13 by ivork         ########   odam.nl         */
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

	while (**str_dup != '\0')
	{
		if (**str_dup == delimiter)
		{
			end = *str_dup;
			(*str_dup)++;
			return(end);
		}
		(*str_dup)++;
	}
	return (*str_dup);
}

char	*find_end_word(char **str_dup)
{
	char	*end;

	end = NULL;
	while (**str_dup != '\0')
	{
		if (**str_dup == ' ')
		{
			return (*str_dup);
		}
		(*str_dup)++;
	}
	end = (*str_dup)--;
	return (end);
}

char 	*handle_quotes(char **str_dup, char delimiter)
{
	char		*start;
	char		*end;
	char		*str;

	(*str_dup)++;
	start = *str_dup;
	end = find_closing_quote(str_dup, delimiter);
	str = malloc((end - start + 1) * sizeof(char));
	ft_strlcpy(str, start, end - start + 1);
	return (str);
}

char 	*handle_spaces(char **str_dup)
{
	char		*start;
	char		*end;
	char		*str;

	start = *str_dup;
	end = find_end_word(str_dup);
	str = malloc((end - start + 1) * sizeof(char));
	ft_strlcpy(str, start, end - start + 1);
	return (str);
}

char *split_user_input(char **str_dup)
{
	while (**str_dup == ' ')
		(*str_dup)++;
	if (!(**str_dup))
		return (NULL);
	if (**str_dup == '\'')
		return(handle_quotes(str_dup, '\''));
	if (**str_dup == '\"')
		return(handle_quotes(str_dup, '\"'));
	if (**str_dup != ' ')
		return(handle_spaces(str_dup));
	return (NULL);
}

t_llnode	*create_linked_list(char *str)
{
	t_llnode *head;
	t_llnode *tmp;
	char	*argument;

	head = NULL;
	while (*str != '\0')
	{
		argument = split_user_input(&str);
		if (argument)
		{
			if (head != NULL)
			{
				tmp = create_new_node();
				tmp->str = argument;
				add_list_front(&head, tmp);
			}
			else
			{
				head = create_new_node();
				head->str = argument;	
			}
		}
		if (*str)
			str++;
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
	while (head != NULL)
	{
		printf("|%s|\n", head->str);
		head = head->next;
	}
}

t_llnode	*parser(char *str)
{
	t_llnode *head;
	head = create_linked_list(str);
	return (head);
}

// int	main(void)
// {
// 	char	*str = "\'ls \' \"-la\"              grep \'|\' \"wc\" \'-l1234      \'         ";
// 	char *s = "\'ls\' -la";
// 	t_llnode *head;

// 	printf("before = %p\n", head);
// 	head = create_linked_list(s);
// 	printf("after = %p\n", head);

// 	print_list(head);
// 	free_linked_list(head);
// 	return (0);
// }