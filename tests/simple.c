#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../includes/parser.h"

Test(quotes, zonder_quotes)
{
    char *s = "ls";
    char **ret = parser(s);
    cr_assert(eq(str, "ls", ret[0]));
}

Test(quotes, single_quotes)
{
    char *s = "\'ls\'";
    char **ret = parser(s);
    cr_assert(eq(str, "ls", ret[0]));
}

Test(quotes, double_quotes)
{
    char *s = "\"ls\"";
    char **ret = parser(s);
    cr_assert(eq(str, "ls", ret[0]));
}

Test(quotes, met_flags)
{
    char *s = "ls -lta";

    char **ret = parser(s);
    char *output[2] = {"ls", "-lta"};
    cr_assert(eq(str, output[0], ret[0]));
    cr_assert(eq(str, output[1], ret[1]));
}

Test(quotes, cmds_quotes_options_no_quotes)
{
    char *s = "\'ls\' -la";

    char **ret = parser(s);
    char *output[2] = {"ls", "-la"};
    cr_assert(eq(str, output[0], ret[0]));
    cr_assert(eq(str, output[1], ret[1]));
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
