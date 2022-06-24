/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 16:30:36 by ivork         #+#    #+#                 */
/*   Updated: 2022/06/21 16:44:39 by kgajadie      ########   odam.nl         */
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

char *find_closing_single_quote(char *str, size_t *i)
{
    char *end = NULL;
    while (str[*i])
    {
        if (str[*i] == '\'')
        {
            end = str + (*i - 1);
            (*i)++;
            break;
        }
        (*i)++;
    }
    return (end);
}

char *find_closing_double_quote(char *str, size_t *i)
{
    char *end = NULL;
    while (str[*i])
    {
        if (str[*i] == '\"')
        { 
            end = str + (*i - 1);
            (*i)++;
            break;
        }
        (*i)++;
    }
    return (end);
}

char *find_end_word(char *str, size_t *i)
{
    char *end = NULL;
    while (str[*i])
    {
        if (str[*i] == ' ')
        { 
            // end = str + (*i - 1);
            // (*i)++;
            break;
        }
        (*i)++;
    }
    (*i)--;
    return (str + *i);
}

int main(void)
{
    char *start = NULL;
    char *end = NULL;
    char *str = "\'ls \' \"-la\" grep";
    char *ret_1 = calloc(10, sizeof(*ret_1));
    char *ret_2 = calloc(10, sizeof(*ret_2));
    char *ret_3 = calloc(10, sizeof(*ret_3));
    char *rets[3] = {ret_1, ret_2, ret_3};
    size_t i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\'')
        {
            i++;
            start = str + i;
            end = find_closing_single_quote(str, &i);
            ft_strlcpy(ret_1, start, end - start + 2);
            printf("rets[0] = |%s|\n", rets[0]);
        }
        if (str[i] == '\"')
        {
            i++;
            start = str + i;
            end = find_closing_double_quote(str, &i);
            ft_strlcpy(ret_2, start, end - start + 2);
            printf("rets[1] = |%s|\n", rets[1]);
        }
        if (str[i] != ' ')
        {
            start = str + i;
            end = find_end_word(str, &i);
            ft_strlcpy(ret_3, start, end - start + 2);
            printf("rets[2] = |%s|\n", rets[2]);
        }
        i++;
    }

    return (0);
}

// int main(void)
// {
//     char *start = NULL;
//     char *end = NULL;
//     char *str = "\'ls \' -la";
//     char *ret = calloc(10, sizeof(*ret));
//     size_t i = 0;

//     while (str[i] != '\0')
//     {
//         if (str[i] == '\'')
//         {
//             if (start == NULL)
//                 start = str + i;
//             else
//                 end = str + i;
//         }
//         if (start != NULL && end != NULL)
//         {
//             ft_strlcpy(ret, start, end - start + 2);
//             start = NULL;
//             end = NULL;
//         }

//         if (str[i] == '\'')
//         i++;
//     }

//     printf("ret = |%s|\n", ret);
//     return (0);
// }
