#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(quotes, zonder_quotes,  .init=redirect_all_std)
{
    char *s = "ls";
    parser(s);
	cr_assert_stdout_eq_str("ls");
}

Test(quotes, single_quotes)
{
    char *s = "\'ls\'";
    parser(s);
	cr_assert_stdout_eq_str("ls");
}

Test(quotes, double_quotes)
{
    char *s = "\"ls\"";
    parser(s);
	cr_assert_stdout_eq_str("ls");
}

Test(quotes, met_flags)
{
    char *s = "ls -lta";

    parser(s);
	cr_assert_stdout_eq_str("ls\n-lta\n");
}

Test(quotes, cmd_quotes_option_no_quotes)
{
    char *s = "\'ls\' -la";

    parser(s);
	cr_assert_stdout_eq_str("ls\n-la\n");
}

Test(quotes, quote_cmd_space_quote_)
{
    char *s = "\'ls \' -la";
    parser(s);
	cr_assert_stdout_eq_str("ls \n-la\n");
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
