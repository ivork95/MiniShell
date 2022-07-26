#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../includes/parser.h"
#include "../includes/minishell.h"
#include "../src/libft/libft.h"

void    handle_spaces_test(char *input, char *expected)
{
    char *submitted;
    submitted = handle_spaces(&input);
        cr_assert_str_eq( submitted, expected, "called handle_spaces():\ninput:\t%s$\nexpected: %s$\n", submitted, expected);
}
Test(handle_spaces, fixed)
{
    handle_spaces_test((char *){"ls"} ,"ls");
    handle_spaces_test((char *){"ls  "}, "ls");
}
/* HANDLE_SPACES */
Test(test_handle_spaces, str1)
{
    char *test_string = "ls"; 
    cr_assert_str_eq( handle_spaces(&test_string), "ls");
}

Test(test_handle_spaces, str2)
{
    char *test_string = "ls  "; 
    cr_assert_str_eq(handle_spaces(&test_string), "ls");
}

Test(test_handle_spaces, str3)
{
    char *test_string = "ls -la"; 
    cr_assert_str_eq(handle_spaces(&test_string), "ls");
}

Test(test_handle_spaces, str4)
{
    char *test_string = "ls      "; 
    cr_assert_str_eq(handle_spaces(&test_string), "ls");
}

/* HANDLE_QUOTES */
/* SINGLE_QUOTES */
Test(test_handle_quotes, single_quotes_str1)
{
    char *test_string = "\'ls\' -la";
    cr_assert_str_eq(handle_quotes(&test_string, '\''), "ls");
}

Test(test_handle_quotes, single_quotes_str2)
{
    char *test_string = "\' ls\'";
    cr_assert_str_eq(handle_quotes(&test_string, '\''), " ls");
}

Test(test_handle_quotes, single_quotes_str3)
{
    char *test_string =  "\'ls \'";
    cr_assert_str_eq(handle_quotes(&test_string, '\''), "ls ");
}

Test(test_handle_quotes, single_quotes_str4)
{
    char *test_string ="\'ls\'     ";
    cr_assert_str_eq(handle_quotes(&test_string, '\''), "ls");
}

/* DOUBLE_QUOTES */
Test(test_handle_quotes, double_quotes_str1)
{
    char *test_string = "\"ls\"";
    cr_assert_str_eq(handle_quotes(&test_string, '\"'), "ls");
}

Test(test_handle_quotes, double_quotes_str2)
{

    char *test_string = "\" ls\"";
    cr_assert_str_eq(handle_quotes(&test_string, '\"'), " ls");
}

Test(test_handle_quotes, double_quotes_str3)
{
    char *test_string = "\"ls \"";
    cr_assert_str_eq(handle_quotes(&test_string, '\"'), "ls ");
}

Test(test_handle_quotes, double_quotes_str4)
{
    char *test_string = "\"ls\"     ";
    cr_assert_str_eq(handle_quotes(&test_string, '\"'), "ls");
}

/* PARSER */
Test(test_parser, met_flags)
{
    char *test_string = "ls -lta";
    t_llnode *arguments = parser(test_string);
    char *output[2] = {"ls", "-lta"};
    
    cr_assert(eq(str, output[1], arguments->str));
    arguments = arguments->next;
    cr_assert(eq(str, output[0], arguments->str));
}

Test(test_parser, cmd_quotes_option_no_quotes)
{
    char *test_string = "\'ls\' -la";

    t_llnode *arguments = parser(test_string);
    char *output[2] = {"ls", "-la"};

    cr_assert(eq(str, output[1], arguments->str));
    arguments = arguments->next;
    cr_assert(eq(str, output[0], arguments->str));
}

Test(test_parser, quote_cmd_space_quote_)
{
    char *test_string = "\'ls \' -la";

    t_llnode *arguments = parser(test_string);
    char *output[2] = {"ls ", "-la"};
    cr_assert(eq(str, output[1], arguments->str));
    arguments = arguments->next;
    cr_assert(eq(str, output[0], arguments->str));
}

Test(test_parser, cmd_operator_no_space_)
{
    char *test_string = "ls -la|grep a.out";

    t_llnode *arguments = parser(test_string);
    char *output[5] = {"ls ", "-la", "|", "grep", "a.out"};

    int i = 4;
    while (arguments)
    {
        cr_assert(eq(str, output[i], arguments->str));
        arguments = arguments->next;
        i--;
    }
}

Test(test_parser, cmd_quotes_no_space_)
{
    char *test_string = "echo test\'<\'hello";

    t_llnode *arguments = parser(test_string);
    char *output[2] = {"echo", "test<hello"};

    int i = 1;
    while (arguments)
    {
        cr_assert(eq(str, output[i], arguments->str));
        arguments = arguments->next;
        i--;
    }
}

Test(test_parser, long_string)
{
    char *test_string = "\'ls \' -la | \"grep\" libft \'hello   \'           world      ";
    char *output[7] = {"world", "hello   ", "libft", "grep", "|", "-la", "ls "};
    
    t_llnode *arguments = parser(test_string);
    int i = 0;
    while (arguments)
    {
        cr_assert(eq(str, output[i], arguments->str));
        arguments = arguments->next;
        i++;
    }
}

Test(test_parser, is_closed)
{
    char *s_closed = "\"ls\"";
    int is_closed = closed_quotes(s_closed);
    cr_assert(is_closed, "string is niet geclosed!");

    char *s_niet_closed = "\"ls";
    is_closed = closed_quotes(s_niet_closed);
    cr_assert(ne(is_closed, "string is geclosed!"));
}

Test(test_tokenizer, cmd_line)
{
	char	*s = "\'helloo\'   world|test  ||   this \"string   \"        \"forme\"<outfile>>       \"quotes > not | closed  ";
	t_tokens	*list;

	list = tokenizer(s);
    char *output[13] = {"\'helloo\'", "world","|","test",  "|", "|"  ,"this", "\"string   \"",   "\"forme\"", "<", "outfile", ">>", "\"quotes > not | closed  "};

    int i = 0;
    while (list)
    {
        char *test_str = malloc(sizeof(char *) * list->len + 1);
        ft_strlcpy(test_str, list->str, list->len + 1);
        cr_assert(eq(str, output[i], test_str));
        list = list->next;
        free(test_str);
        i++;
    }
}

/*
gcc simple.c \
../src/parser/parser.c \
../src/parser/is_closed.c \
../src/libft/libft.a \
../src/tokenizer/tokenizer.c \ 
../src/tokenizer/tokenizer_utils.c \ 
-lcriterion
*/
