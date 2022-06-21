/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 16:30:36 by ivork         #+#    #+#                 */
/*   Updated: 2022/06/21 13:16:45 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>

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

int main(void)
{
    char *start = NULL;
    char *end = NULL;
    char *str = "\'ls \' -la";
    char *ret = calloc(10, sizeof(*ret));
    size_t i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\'')
        {
            if (start == NULL)
                start = str + i;
            else
                end = str + i;
        }
        if (start != NULL && end != NULL)
        {
            ft_strlcpy(ret, start, end - start + 2);
            start = NULL;
            end = NULL;
        }
        i++;
    }

    printf("ret = |%s|\n", ret);
    return (0);
}
