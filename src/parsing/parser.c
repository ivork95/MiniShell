/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 16:30:36 by ivork         #+#    #+#                 */
/*   Updated: 2022/06/10 17:30:00 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char **parser(char *line)
{
	char **splitted_lines;
	
	splitted_lines = ft_split(line, ' ');
	return (splitted_lines);
}