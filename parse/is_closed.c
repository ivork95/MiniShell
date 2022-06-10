/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_closed.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:21:29 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/06/10 15:21:47 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>

int	closed_quotes(char *str)
{
	if (str[0] == '\'')
	{
		if (strchr(str + 1, '\''))
			return (true);
	}
	if (str[0] == '\"')
	{
		if (strchr(str + 1, '\"'))
			return (true);
	}
	return (false);
}
