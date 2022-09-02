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

static void	setup(void)
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
