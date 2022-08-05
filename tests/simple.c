#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"

Test(parser, echo_hello_world)
{
    t_command   *command;
    t_token     *tokens;
    char        *input;

    input = "echo hello world";
    tokens = tokenizer(input);
    command = parser(tokens);

    cr_assert(eq(str, "echo", command->cmd));
    cr_assert(eq(str, "echo", command->args[0]));
    cr_assert(eq(str, "hello", command->args[1]));
    cr_assert(eq(str, "world", command->args[2]));
    cr_assert(zero(ptr,command->next));
}

Test(parser, two_commands)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "ls -la | grep Makefile";
    tokens = tokenizer(input);
    commands = parser(tokens);

    cr_assert(eq(str, "ls", commands->cmd));
    cr_assert(eq(str, "ls", commands->args[0]));
    cr_assert(eq(str, "-la", commands->args[1]));
    cr_assert(zero(ptr, commands->files));

    commands = commands->next;

    cr_assert_str_eq(commands->cmd, "grep");
    cr_assert_str_eq(commands->args[0], "grep");
    cr_assert_str_eq(commands->args[1], "Makefile");
    cr_assert(zero(ptr, commands->files));
    cr_assert(zero(ptr, commands->next));
}

Test(parser, two_redirections)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "< infile cat > outfile";
    tokens = tokenizer(input);
    commands = parser(tokens);

    cr_assert(eq(str, "cat", commands->cmd));
    cr_assert(eq(str, "cat", commands->args[0]));
    cr_assert(eq(int, 0, commands->files->type));
    cr_assert(eq(str, "infile", commands->files->file_name));

    commands->files = commands->files->next;

    cr_assert(eq(int, 1, commands->files->type));
    cr_assert(eq(str, "outfile", commands->files->file_name));
    cr_assert(zero(ptr, commands->next));
}

/*
gcc simple.c \
../src/parser/parser.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
../src/libft/libft.a \
-lcriterion
*/