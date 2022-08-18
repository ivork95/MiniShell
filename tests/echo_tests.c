#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/builtins.h"
#include <fcntl.h>

extern char **environ;

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(builtin_echo, simple, .init=redirect_all_std)
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

Test(builtin_echo, empty, .init=redirect_all_std)
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

Test(builtin_echo, simple_no_new_line, .init=redirect_all_std)
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

// Test(builtin_echo, echo_to_outfile, .init=redirect_all_std)
// {
//     t_command *commands;
//     t_token *tokens;
//     char *input;
//     char *expect= "";

//     input = "echo hello world > outfile.txt";
//     tokens = tokenizer(input);
//     commands = parser(tokens);
//     expander(commands, environ);
//     echo_builtin(commands);
// 	// int outfile = open("../../outfile.txt", O_RDONLY);
// 	FILE *fp;
// 	printf("test!!!!!!!!!\n");
// 	fp=fopen("../../outfile.txt", "r");
// 	printf("file pointer = %p\n", fp);
// 	cr_assert_file_contents_eq_str(fp, "hello world\n");
//     //assert equal file contents
// }

// Test(builtin_echo, echo_append_outfile, .init=redirect_all_std)
// {
//     t_command *commands;
//     t_token *tokens;
//     char *input;
//     char *expect= "";

//     input = "echo hello world >> outfile";
//     tokens = tokenizer(input);
//     commands = parser(tokens);
//     expander(commands, environ);
//     echo_builtin(commands);

//     //assert equal file contents
// }

// Test(builtin_echo, echo_double_redirect, .init=redirect_all_std)
// {
//     t_command *commands;
//     t_token *tokens;
//     char *input;
//     char *expect= "";

//     input = "echo hello world > outfile > outfile2";
//     tokens = tokenizer(input);
//     commands = parser(tokens);
//     expander(commands, environ);
//     echo_builtin(commands);

//     //assert equal file contents
// }

// Test(builtin_echo, echo_append_and_redirect_out, .init=redirect_all_std)
// {
//     t_command *commands;
//     t_token *tokens;
//     char *input;
//     char *expect= "";

//     input = "echo hello world >> outfile > outfile2";
//     tokens = tokenizer(input);
//     commands = parser(tokens);
//     expander(commands, environ);
//     echo_builtin(commands);

//     //assert equal file contents
// }