/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 16:30:36 by ivork         #+#    #+#                 */
/*   Updated: 2022/06/16 15:11:07 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

void remove_quotes(char **line)
{
    char type_of_quote;
    printf("line = |%s|\n", *line);

    if (*line[0] == '\'')
        type_of_quote = '\'';
    else if (*line[0] == '\"')
        type_of_quote = '\"';
    else
        type_of_quote = 0;
    if (type_of_quote)
    {
        (*line)++;
        (*line)[ft_strlen(*line) - 1] = '\0';
    }
}

char **parser(const char *line)
{
    char **splitted_lines;
    size_t i;

    i = 0;
    splitted_lines = ft_split(line, ' ');
    // printf("splitted_lines[0] = |%s|\n", splitted_lines[0]);
    while (splitted_lines[i] != NULL)
    {
        remove_quotes(splitted_lines + i);
        i++;
    }
    // printf("splitted_lines[1] = |%s|\n", splitted_lines[0]);
    return (splitted_lines);
}

// int main(void)
// {
//     char *s = "\'ls\'";
//     char **ret = parser(s);
// }
