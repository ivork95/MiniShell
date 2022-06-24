#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef struct s_llnode
{
    char            *str;
    struct s_llnode  *next;
}   t_llnode;

void print_arguments(char *str, long int length)
{
	int  i;

	i = 0;
    printf("|");
	while(length > i)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("|\n");
}

// t_llnode    *create(char *str, t_llnode *old)
// {
//     t_llnode    *new;

//     new->str = astr
//     if (new->str == NULL)
//         exit(EXIT_FAILURE);
//     new->next = old;
// }

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

void handle_single_quotes(char **str_dup, t_llnode **head)
{
    char        *start;
    char        *end;
    char        *string;
    t_llnode    *next;

    (*str_dup)++;
    start = *str_dup;
    end = find_closing_single_quote(str_dup);
    print_arguments(start, end - start);

    next = malloc(sizeof(*next));
    if (next == NULL)
        exit(EXIT_FAILURE);
    next->str = malloc(end - start + 1);
    ft_strlcpy(next->str, start, end - start + 1);
    next->next = *head;
    *head = next;
}

void handle_double_quotes(char **str_dup, t_llnode **head)
{
    char        *start;
    char        *end;
    char        *string;
    t_llnode    *next;

    (*str_dup)++;
    start = *str_dup;
    end = find_closing_double_quote(str_dup);
    print_arguments(start, end - start);

    next = malloc(sizeof(*next));
    if (next == NULL)
        exit(EXIT_FAILURE);
    next->str = malloc(end - start + 1);
    ft_strlcpy(next->str, start, end - start + 1);
    next->next = *head;
    *head = next;
}

// void handle_double_quotes(char **str_dup)
// {
//     char    *start;
//     char    *end;

//     (*str_dup)++;
//     start = *str_dup;
//     end = find_closing_double_quote(str_dup);
//     print_arguments(start, end - start);
// }

void handle_spaces(char **str_dup)
{
    char    *start;
    char    *end;

    start = *str_dup;
    end = find_end_word(str_dup);
    print_arguments(start, end - start);
}

void beta(t_llnode **head, char *str)
{
    char    *str_dup;

    str_dup = str;
    while (*str_dup != '\0')
    {
        if (*str_dup == '\'')
            handle_single_quotes(&str_dup, head);
        if (*str_dup == '\"')
            handle_double_quotes(&str_dup, head);
        if (*str_dup != ' ')
            handle_spaces(&str_dup);
        str_dup++;
    }
}

int main(void)
{
    char *str = "\'ls \' \"-la\" grep";

    t_llnode *head;
    head = malloc(sizeof(*head));
    if (head == NULL)
        exit(EXIT_FAILURE);
    head->next = NULL;

    printf("before = %p\n", head);
    beta(&head, str);
    printf("after = %p\n", head);

    while (head->next != NULL)
    {
        printf("|%s|\n", head->str);
        head = head->next;
    }
}
