/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:03:53 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/12 10:08:47 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

bool	ft_isspace(int c)
{
	if (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ')
		return (true);
	else
		return (false);
}

bool	isspecialchar(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

void	print_tokens(t_token *head)
{
	size_t	i;

	i = 0;
	while (head != NULL)
	{
		printf("node[%lu] = {\n\tstr = $%.*s$\n\tlen = %lu\n\ttype = %lu\n\tquoted = %i\n}\n", i, (int)head->len, head->str, head->len, head->type, head->quoted);
		head = head->next;
		i++;
	}
}

void	free_tokens(t_token *head)
{
	if (head->next)
		free_tokens(head->next);
	free(head);
}
