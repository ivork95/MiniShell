#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../includes/parser.h"

Test(quotes, zonder_quotes)
{
    char *test_string = "ls";
    char *test_string2 = "ls  ";
    char *test_string3 = "ls -la";
    char *test_string4 = "ls      ";
    cr_assert_str_eq("ls", handle_spaces(&test_string));
    cr_assert_str_eq("ls", handle_spaces(&test_string2));
    cr_assert_str_eq("ls", handle_spaces(&test_string3));
    cr_assert_str_eq("ls", handle_spaces(&test_string4));
}

Test(quotes, single_quotes)
{
    char *test_string = "\'ls\' -la";
    char *test_string2 = "\' ls\'";
    char *test_string3 = "\'ls \'";
    char *test_string5 = "\'ls\'     ";
    cr_assert_str_eq("ls", handle_quotes(&test_string, '\''));
    cr_assert_str_eq(" ls", handle_quotes(&test_string2, '\''));
    cr_assert_str_eq("ls ", handle_quotes(&test_string3, '\''));
    cr_assert_str_eq("ls", handle_quotes(&test_string5, '\''));
}


Test(quotes, double_quotes)
{
    char *test_string = "\"ls\"";
    char *test_string2 = "\" ls\"";
    char *test_string3 = "\"ls \"";
    char *test_string5 = "\"ls\"     ";
    cr_assert_str_eq("ls", handle_quotes(&test_string, '\"'));
    cr_assert_str_eq(" ls", handle_quotes(&test_string2, '\"'));
    cr_assert_str_eq("ls ", handle_quotes(&test_string3, '\"'));
    cr_assert_str_eq("ls", handle_quotes(&test_string5, '\"'));
}


Test(quotes, met_flags)
{
    char *s = "ls -lta";
    t_llnode *arguments = parser(s);
    char *output[2] = {"ls", "-lta"};
    
    cr_assert(eq(str, output[1], arguments->str));
    arguments = arguments->next;
    cr_assert(eq(str, output[0], arguments->str));
}

Test(quotes, cmd_quotes_option_no_quotes)
{
    char *s = "\'ls\' -la";

    t_llnode *arguments = parser(s);
    char *output[2] = {"ls", "-la"};

    cr_assert(eq(str, output[1], arguments->str));
    arguments = arguments->next;
    cr_assert(eq(str, output[0], arguments->str));
}

Test(quotes, quote_cmd_space_quote_)
{
    char *s = "\'ls \' -la";

    t_llnode *arguments = parser(s);
    char *output[2] = {"ls ", "-la"};
    cr_assert(eq(str, output[1], arguments->str));
    arguments = arguments->next;
    cr_assert(eq(str, output[0], arguments->str));
}

Test(quotes, is_closed)
{
    char *s_closed = "\"ls\"";
    int is_closed = closed_quotes(s_closed);
    cr_assert(is_closed, "string is niet geclosed!");

    char *s_niet_closed = "\"ls";
    is_closed = closed_quotes(s_niet_closed);
    cr_assert(ne(is_closed, "string is geclosed!"));
}


/*
gcc simple.c \
../src/parser/parser.c \
../src/parser/is_closed.c \
../src/libft/libft.a \
-lcriterion
*/
