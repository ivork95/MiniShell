#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"
#include "../includes/expander.h"
#include "../includes/builtins.h"

extern char **environ;
t_env_var	*head;

void	setup(void)
{
	head = environ_to_linked_list_recursive(head, environ);
}

Test(expander, quotes, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "\'echo\' hello world";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello", commands->args[1]));
    cr_assert(eq(str, "world", commands->args[2]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, double_quotes, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \'hello\'\'world\'";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "helloworld", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, evnp_home, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo $HOME";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "/root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, double_envp, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo $HOME$HOME";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "/root/root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, envp_with_dollar, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo $HOME$";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "/root$", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, evnp_home_quoted, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \'$HOME\'";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "$HOME", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, evnp_home_double_quoted, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \"$HOME\"";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "/root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, sandwichde_quotes, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "e'ch'o \"hell\"o world";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello", commands->args[1]));
    cr_assert(eq(str, "world", commands->args[2]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, single_quotes_inside_double, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "e'ch'o \"hello '$HOME'\"";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello '/root'", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, double_quotes_inside_double, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \"hello \"$HOME\"\"";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello /root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, linked_expanstion, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo test$HOME";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "test/root", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, linked_expanstion_rev, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo $HOMEtest";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, single_quote_expantion, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo 'hello'$HOME'bye'";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello/rootbye", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, double_quotes_remove, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \"hello\"$HOME\"bye\"";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello/rootbye", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

Test(expander, multiple_quotes_inside, .init = setup)
{
    t_command *commands;
    t_token *tokens;
    char *input;

    input = "echo \"hello 'test' 'this' 'string' bye\"";
    tokens = tokenizer(input);
    commands = parser(tokens);
    expander(commands, head);

    cr_assert(eq(str, "echo", commands->cmd));
    cr_assert(eq(str, "echo", commands->args[0]));
    cr_assert(eq(str, "hello 'test' 'this' 'string' bye", commands->args[1]));
    cr_assert(zero(ptr, commands->next));
}

/*
gcc \
expander_tests.c \
-lcriterion \
../src/parser/parser.c \
../src/heredoc/heredoc.c \
../src/minishell_utils.c \
../src/parser/parser_utils.c \
../src/expander/expander.c \
../src/expander/expander_utils.c \
../src/expander/expander_data.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
../src/builtins/env.c \
../src/builtins/export.c \
../src/builtins/unset.c \
../src/builtins/change_dir.c \
../src/builtins/echo.c \
../src/builtins/pwd.c \
-L../src/libft -l:libft.a
*/