/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 16:30:36 by ivork         #+#    #+#                 */
/*   Updated: 2022/06/16 14:56:30 by kgajadie      ########   odam.nl         */
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

void remove_quotes(char **line)
{
    char type_of_quote;

    if (*line[0] == '\'')
        type_of_quote = '\'';
    else if (*line[0] == '\"')
        type_of_quote = '\"';
    else
        type_of_quote = 0;
    if (type_of_quote)
    {
        printf("line = |%s|\n", *line);
        (*line)++;
        printf("line = |%s|\n", *line);
        (*line)[ft_strlen(*line) - 1] = '\0';
    }
    printf("line = |%s|\n", *line);
}

char **parser(const char *line)
{
    char **splitted_lines;
    size_t i;

    i = 0;
    splitted_lines = ft_split(line, ' ');
    while (splitted_lines[i] != NULL)
    {
        remove_quotes(splitted_lines + i);
        i++;
    }

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