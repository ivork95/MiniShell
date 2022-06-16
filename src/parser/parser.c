/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 16:30:36 by ivork         #+#    #+#                 */
/*   Updated: 2022/06/16 12:40:25 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

// char **parser(char *line)
// {
// 	char **splitted_lines;
	
// 	splitted_lines = ft_split(line, ' ');
// 	return (splitted_lines);
// }

char **parser(char *line)
{
    char *line_dup;
    char **splitted_lines;
    char type_of_quote;

    line_dup = ft_strdup(line);
    if (line_dup[0] == '\'')
        type_of_quote = '\'';
    else if (line_dup[0] == '\"')
        type_of_quote = '\"';
    else
        type_of_quote = 0;

    if (type_of_quote)
    {
        line_dup++;
        line_dup[ft_strlen(line_dup) - 1] = '\0';
    }
    splitted_lines = ft_split(line_dup, ' ');
    return (splitted_lines);
}

// int main(void)
// {
//     char *s = "\'ls\'";
//     char **ret = parser(s);
//     printf("ret[0] = |%s|\n", ret[0]);
//     printf("ret[1] = |%s|\n", ret[1]);
// }

/*
Voor de single quotest test
moeten we niet ook een 2d array returnen -> {"ls", null}?
met als input "\'ls\'"
*/