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
    char    *end;

    end = NULL;
    while (**str_dup != '\0')
    {
        if (**str_dup == ' ')
            return (*str_dup);
        (*str_dup)++;
    }
    end = (*str_dup)--;
    return (end);
}


void print_arguments(char *str, long int length)
{
	int  i;

	i = 0;
	while(length > i)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}

void parser(const char* str)
{
    // char *ret_1 = calloc(10, sizeof(*ret_1));
    // char *ret_2 = calloc(10, sizeof(*ret_2));
    // char *ret_3 = calloc(10, sizeof(*ret_3));

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
			// printf("%ld\n", end - start);
            // ft_strlcpy(ret_1, start, end - start + 1);
            // printf("ret_1 = |%s|\n", ret_1);
        }
        if (*str_dup == '\"')
        {
            str_dup++;
            start = str_dup;
            end = find_closing_double_quote(&str_dup);
			print_arguments(start, end - start);
            // ft_strlcpy(ret_2, start, end - start + 1);
            // printf("ret_2 = |%s|\n", ret_2);
        }
        if (*str_dup != ' ')
        {
            start = str_dup;
            end = find_end_word(&str_dup);
			print_arguments(start, end - start);
            // ft_strlcpy(ret_3, start, end - start + 1);
            // printf("ret_3 = |%s|\n", ret_3);
        }
        str_dup++;
    }
}

// int main(void)
// {
//     const char *str = "\'ls \'        \"-la \" grep    ";
//     alpha(str);
// }