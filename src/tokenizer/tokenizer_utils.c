/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:03:53 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/07/21 11:54:02 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		printf("node[%lu]->str = $%.*s$\n", i, (int)head->len, head->str);
		head = head->next;
		i++;
	}
}
