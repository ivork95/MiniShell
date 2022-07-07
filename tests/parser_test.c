#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

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
    char *test_string = "\'ls\'";
    char *test_string2 = "\' ls\'";
    char *test_string3 = "\'ls \'";
    char *test_string5 = "\'ls\'     ";
    cr_assert_str_eq("ls", handle_quotes(&test_string, '\''));
    cr_assert_str_eq(" ls", handle_quotes(&test_string2, '\''));
    cr_assert_str_eq("ls ", handle_quotes(&test_string3, '\''));
    cr_assert_str_eq("ls", handle_quotes(&test_string5, '\''));
}

// void    parser_test()
// {
//     Parser
// }
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
    t_llnode *arguments;

    char *s = "\'ls\'";
    char *expect[] = {"ls"};
    int i = 0;
    arguments = parser(s);
    while (arguments->next)
    {
        cr_assert_str_eq(arguments->str, expect[i]);
        arguments = arguments->next;
        i++;

    }
}

// Test(quotes, cmd_quotes_option_no_quotes)
// {
//     char *s = "\'ls\' -la";

//     parser(s);
// 	cr_assert_stdout_eq_str("ls\n-la\n");
// }

// Test(quotes, quote_cmd_space_quote_)
// {
//     char *s = "\'ls \' -la";
//     parser(s);
// 	cr_assert_stdout_eq_str("ls \n-la\n");
// }

// Test(quotes, is_closed)
// {
//     char *s_closed = "\"ls\"";
//     int is_closed = closed_quotes(s_closed);
//     cr_assert(is_closed, "string is niet geclosed!");

//     char *s_niet_closed = "\"ls";
//     is_closed = closed_quotes(s_niet_closed);
//     cr_assert(ne(is_closed, "string is geclosed!"));
// }
