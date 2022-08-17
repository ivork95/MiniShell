#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/builtins.h"

extern char **environ;

Test(builtin_echo, simple)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "hello world\n";

    input = "echo hello world";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    cr_assert_stdout_eq_str(expect);
}

Test(builtin_echo, empty)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "\n";

    input = "echo";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    cr_assert_stdout_eq_str(expect);
}

Test(builtin_echo, simple_no_new_line)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "hello world";

    input = "echo -n hello world";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    cr_assert_stdout_eq_str(expect);
}

Test(builtin_echo, echo_to_outfile)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "";

    input = "echo hello world > outfile";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    //assert equal file contents
}

Test(builtin_echo, echo_to_outfile)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "";

    input = "echo hello world >> outfile";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    //assert equal file contents
}

Test(builtin_echo, echo_double_redirect)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "";

    input = "echo hello world > outfile > outfile2";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    //assert equal file contents
}

Test(builtin_echo, echo_append_and_redirect_out)
{
    t_command *commands;
    t_token *tokens;
    char *input;
    char *expect= "";

    input = "echo hello world >> outfile > outfile2";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, environ);
    echo_builtin(commands);

    //assert equal file contents
}