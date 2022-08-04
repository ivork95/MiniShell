/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:03:53 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/04 13:10:31 by ivork         ########   odam.nl         */
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

void	print_tokens(t_tokens *head)
{
	size_t	i;

	i = 0;
	printf("head->str = $%s$\n", head->str);
	while (head != NULL)
	{
		printf("node[%lu]->str = $%.*s$  |  type = %d\n", i, (int)head->len, head->str, head->quoted);
		head = head->next;
		i++;
	}
}
