#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

char *find_closing_single_quote(char **str_dup)
{
    char    *end;

    end = NULL;
    while (**str_dup != '\0')
    {
        if (**str_dup == '\'')
        {
            end = *str_dup;
            (*str_dup)++;
            break;
        }
        (*str_dup)++;
    }
    return (end);
}

char *find_closing_double_quote(char **str_dup)
{
    char    *end;

    end = NULL;
    while (**str_dup != '\0')
    {
        if (**str_dup == '\"')
        {
            end = *str_dup;
            (*str_dup)++;
            break;
        }
        (*str_dup)++;
    }
    return (end);
}

char *find_end_word(char **str_dup)
{
    while (**str_dup != '\0' && **str_dup != ' ')
        (*str_dup)++;
    return((*str_dup)--);
}


void print_arguments(char *str, long int length)
{
    write(1, str, length);
}

void parser(const char* str)
{
    char    *start;
    char    *end;
    char    *str_dup;

    start = NULL;
    end = NULL;
    str_dup = str;

    while (*str_dup != '\0')
    {
        if (*str_dup == '\'')
        {
            str_dup++;
            start = str_dup;
            end = find_closing_single_quote(&str_dup);
			print_arguments(start, end - start);
        }
        if (*str_dup == '\"')
        {
            str_dup++;
            start = str_dup;
            end = find_closing_double_quote(&str_dup);
			print_arguments(start, end - start);
        }
        if (*str_dup != ' ')
        {
            start = str_dup;
            end = find_end_word(&str_dup);
        }
        str_dup++;
    }
}
