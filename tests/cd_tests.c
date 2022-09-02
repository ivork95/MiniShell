#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/tokenizer.h"
#include "../includes/parser.h"
#include "../includes/builtins.h"

extern char	**environ;
static t_env_var	*head;

static void	setup(void)
{
	head = environ_to_linked_list_recursive(head, environ);
}

Test(cd, cd_home, .init = setup)
{
	char		*input_str = "cd";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);
	char *old_pwd;


	old_pwd = getcwd(NULL, 0);
	cd_builtin(cmds, &head);
	cr_assert(eq(str,find_env_var(head, "OLDPWD")->value, old_pwd));
	cr_assert(eq(str,find_env_var(head, "PWD")->value, getcwd(NULL, 0)));
}

Test(cd, change_directory_parent, .init = setup)
{
	char		*input_str = "cd ..";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);
	char *old_pwd;


	old_pwd = getcwd(NULL, 0);
	cd_builtin(cmds, &head);
	cr_assert(eq(str,find_env_var(head, "OLDPWD")->value, old_pwd));
	cr_assert(eq(str,find_env_var(head, "PWD")->value, getcwd(NULL, 0)));
}


/*
gcc \
cd_tests.c \
-lcriterion \
../src/parser/parser.c \
../src/parser/parser_utils.c \
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