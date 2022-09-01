#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/tokenizer.h"
#include "../includes/parser.h"
#include "../includes/builtins.h"

extern char	**environ;
t_env_var	*head;

static unsigned int	count_environ_vars(char **environ)
{
	unsigned int	count;

	count = 0;
	while (*environ != NULL)
	{
		count++;
		environ++;
	}
	return (count);
}

static unsigned int	count_env_vars(t_env_var *head)
{
	unsigned int	count;

	count = 0;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}

static t_env_var	*find_env_var(t_env_var *head, char *key_to_check)
{
	while (head != NULL)
	{
		if (!(ft_strncmp(head->key, key_to_check, ft_strlen(head->key))))
			return (head);
		head = head->next;
	}
	return (head);
}

void	setup(void)
{
	head = environ_to_linked_list_recursive(head, environ);
}

Test(unset, delete, .init = setup)
{
	char		*input_str = "unset HOSTNAME";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	cr_assert_not_null(find_env_var(head, cmds->args[1]));
	unset_builtin(cmds, &head);
	cr_assert(zero(ptr,find_env_var(head, cmds->args[1])));
}

Test(unset, delete_multiple, .init = setup)
{
	char		*input_str = "unset HOSTNAME PWD";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	cr_assert_not_null(find_env_var(head, cmds->args[1]));
	cr_assert_not_null(find_env_var(head, cmds->args[2]));
	unset_builtin(cmds, &head);
	// put_env_vars(head);

	cr_assert(zero(ptr,find_env_var(head, cmds->args[1])));
	cr_assert(zero(ptr,find_env_var(head, cmds->args[2])));
}



/*
gcc \
export_tests.c \
../src/libft/libft.a \
../src/parser/parser.c \
../src/parser/parser_utils.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
-lcriterion
*/

/*
gcc \
unset_tests.c \
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