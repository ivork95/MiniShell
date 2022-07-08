/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/24 16:58:55 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/07/08 13:55:07 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_llnode	*create_new_node(void)
{
	t_llnode	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->str = NULL;
	new->next = NULL;
	return (new);
}

void	add_list_front(t_llnode **head, t_llnode *new_node)
{
	new_node->next = *head;
	*head = new_node;
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
			return (end);
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

char	*handle_quotes(char **str_dup, char delimiter)
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

char	*handle_spaces(char **str_dup)
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

char	*split_user_input(char **str_dup)
{
	while (**str_dup == ' ')
		(*str_dup)++;
	if (!(**str_dup))
		return (NULL);
	if (**str_dup == '\'')
		return (handle_quotes(str_dup, '\''));
	if (**str_dup == '\"')
		return (handle_quotes(str_dup, '\"'));
	if (**str_dup != ' ')
		return (handle_spaces(str_dup));
	return (NULL);
}

void	create_linked_list(t_llnode **head, char *str)
{
	t_llnode	*tmp;
	char		*argument;

	*head = NULL;
	while (*str != '\0')
	{
		argument = split_user_input(&str);
		if (argument)
		{
			if (head != NULL)
			{
				tmp = create_new_node();
				tmp->str = argument;
				add_list_front(head, tmp);
			}
			else
				(*head)->str = argument;
		}
		if (*str)
			str++;
	}
}

void	free_linked_list(t_llnode *head)
{
	if (head->next != NULL)
		free_linked_list(head->next);
	free(head->str);
	free(head);
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
	t_llnode	*head;

	head = create_new_node();
	create_linked_list(&head, str);
	return (head);
}
