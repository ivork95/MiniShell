#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"

Test(expander, quotes)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "\'echo\' \"hello\" world";
    tokens = tokenizer(input);
    commands = parser(tokens);
    commands = expander(commands);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello", commands->args[1]));
    cr_assert(eq(str, "world", commands->args[2]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, evnp_home)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo $HOME";
    tokens = tokenizer(input);
    commands = parser(tokens);
    commands = expander(commands);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "/root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, evnp_home_quoted)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \'$HOME\'";
    tokens = tokenizer(input);
    commands = parser(tokens);
    commands = expander(commands);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "$HOME", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, evnp_home_double_quoted)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \"$HOME\"";
    tokens = tokenizer(input);
    commands = parser(tokens);
    commands = expander(commands);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "/root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}
