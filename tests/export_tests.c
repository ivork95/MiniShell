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

Test(export, clone_env_ll, .init = setup)
{
	unsigned int	ll_count;
	unsigned int	actual_count;
	unsigned int	i;
	char			*tmp_str;
	char			*joined_str;

	ll_count = count_env_vars(head);
	actual_count = count_environ_vars(environ);
	cr_assert(eq(int, actual_count, ll_count));

	i = 0;
	while (i < actual_count)
	{
		tmp_str = ft_strjoin(head->key, "=");
		joined_str = ft_strjoin(tmp_str, head->value);
		free(tmp_str);
		cr_assert_not(ft_strncmp(environ[i], joined_str, ft_strlen(environ[i])));
		free(joined_str);
		head = head->next;
		i++;
	}
}

Test(export, simple_export, .init = setup)
{
	char		*input_str = "export jon=aegon";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	export_builtin(cmds, &head);
	// put_env_vars(head);

	cr_assert_not_null(find_env_var(head, "jon"));
}

Test(export, overwrite, .init = setup)
{
	char		*input_str = "export PWD=KAWISH";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	char *value = find_env_var(head, "PWD")->value;
	cr_assert(eq(str, "/pwd", value));

	export_builtin(cmds, &head);
	value = find_env_var(head, "PWD")->value;
	// put_env_vars(head);

	cr_assert(eq(str, "KAWISH", value));
	// voeg assertion toe die checkt hoeveel entries er
	// met deze key in zitten.
}

Test(export, overwrite_empty_val, .init = setup)
{
	char		*input_str = "export PWD=";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	export_builtin(cmds, &head);
	char *value = find_env_var(head, "PWD")->value;
	// put_env_vars(head);

	cr_assert(eq(str, "\0", value));
}
