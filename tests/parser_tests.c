#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"
#include "../includes/builtins.h"
extern char **environ;

Test(parser, echo_hello_world)
{
    t_command   *command;
    t_token     *tokens;
    char        *input;

	t_env_var *envp;
	envp = environ_to_linked_list_recursive(envp, environ);

    input = "echo hello world";
    tokens = tokenizer(input);
    command = parser(tokens, &envp);

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
	t_env_var *envp = environ_to_linked_list_recursive(envp, environ);
    input = "ls -la | grep Makefile";
    tokens = tokenizer(input);
    commands = parser(tokens, &envp);

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

Test(parser, four_commands)
{
    t_command *commands;
    t_token *tokens;
    char *input;
	t_env_var *envp = environ_to_linked_list_recursive(envp, environ);
    input = "ls -la | grep Makefile | wc -l | hello world";
    tokens = tokenizer(input);
    commands = parser(tokens, &envp);

    cr_assert(eq(str, "ls", commands->cmd));
    cr_assert(eq(str, "ls", commands->args[0]));
    cr_assert(eq(str, "-la", commands->args[1]));
    cr_assert(zero(ptr, commands->files));

    commands = commands->next;

    cr_assert_str_eq(commands->cmd, "grep");
    cr_assert_str_eq(commands->args[0], "grep");
    cr_assert_str_eq(commands->args[1], "Makefile");
    cr_assert(zero(ptr, commands->files));
    
    commands = commands->next;

    cr_assert(eq(str, "wc", commands->cmd));
    cr_assert(eq(str, "wc", commands->args[0]));
    cr_assert(eq(str, "-l", commands->args[1]));
    cr_assert(zero(ptr, commands->files));

    commands = commands->next;

    cr_assert_str_eq(commands->cmd, "hello");
    cr_assert_str_eq(commands->args[0], "hello");
    cr_assert_str_eq(commands->args[1], "world");
    cr_assert(zero(ptr, commands->files));
    cr_assert(zero(ptr, commands->next));
}

Test(parser, two_redirections)
{
    t_command *commands;
    t_token *tokens;
    char *input;
	t_env_var *envp = environ_to_linked_list_recursive(envp, environ);
    input = "< infile cat > outfile";
    tokens = tokenizer(input);
    commands = parser(tokens, &envp);

    cr_assert(eq(str, "cat", commands->cmd));
    cr_assert(eq(str, "cat", commands->args[0]));
    cr_assert(eq(int, 0, commands->files->type));
    cr_assert(eq(str, "infile", commands->files->file_name));

    commands->files = commands->files->next;

    cr_assert(eq(int, 1, commands->files->type));
    cr_assert(eq(str, "outfile", commands->files->file_name));
    cr_assert(zero(ptr, commands->next));
}

Test(parser, sandwiched_redirections)
{
    t_command *commands;
    t_token *tokens;
    char *input;
	t_env_var *envp = environ_to_linked_list_recursive(envp, environ);
    input = "echo hello > outfile world";
    tokens = tokenizer(input);
    commands = parser(tokens, &envp);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello", commands->args[1]));
    cr_assert(eq(str, "world", commands->args[2]));
    cr_assert(eq(int, 1, commands->files->type));
    cr_assert(eq(str, "outfile", commands->files->file_name));
    cr_assert(zero(ptr, commands->next));
}

Test(parser, echo_command_quoted)
{
    t_command   *command;
    t_token     *tokens;
    char        *input;
	t_env_var *envp = environ_to_linked_list_recursive(envp, environ);
    input = "echo \"hello world\"";
    tokens = tokenizer(input);
    command = parser(tokens, &envp);

    cr_assert(eq(str, "echo", command->cmd));
    cr_assert(eq(str, "echo", command->args[0]));
    cr_assert(eq(str, "\"hello world\"", command->args[1]));
    cr_assert(zero(ptr,command->next));
}


/*
gcc parser_tests.c \
../src/parser/parser.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
../src/libft/libft.a \
-lcriterion
*/