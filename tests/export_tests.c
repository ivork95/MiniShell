#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/libft/libft.h"
#include "../includes/tokenizer.h"
#include "../includes/parser.h"

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

void		free_env_vars(t_env_var *head)
{
	t_env_var	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void		delete_env_var(t_env_var **head, char *key)
{
	t_env_var	*tmp;
	t_env_var *envp;
	tmp = NULL;
	envp = *head;
	while (envp)
	{
		if (!ft_strncmp(key, envp->key, ft_strlen(key)))
		{
			if (!tmp)
			{
				tmp = *head;
				*head = envp->next;
			}
			else
			{
				tmp->next = envp->next;
				tmp = envp;
			}
			tmp->next = NULL;
			free_env_vars(tmp);
			return ;
		}
		tmp = envp;
		envp = envp->next;
	}
}

void		add_front(t_env_var **lst, t_env_var *new)
{
	new->next = *lst;
	*lst = new;
}

void		put_env_vars(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->value, 1);
		head = head->next;
	}
}

void		put_env_vars_declare(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(head->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(head->value, 1);
		ft_putendl_fd("\"", 1);
		head = head->next;
	}
}

t_env_var	*assign_env_key_value(char *env_var, char *ptr)
{
	t_env_var	*head;
	ptrdiff_t	len_key;

	head = malloc(sizeof(*head));
	if (head == NULL)
		exit(EXIT_FAILURE);
	len_key = (ptr - env_var);
	head->key = ft_substr(env_var, 0, len_key);
	if (head->key == NULL)
		exit(EXIT_FAILURE);
	head->value = ft_substr(env_var, len_key + 1, ft_strlen(ptr));
	if (head->value == NULL)
		exit(EXIT_FAILURE);
	return (head);
}

void		add_env_var(t_env_var **head, char *env_var)
{
	char		*ptr;
	t_env_var	*new;

	ptr = ft_strchr(env_var, '=');
	if (ptr == NULL)
		return ; // Geen goede syntax gebruikt -> loesoe
	else
	{
		new = assign_env_key_value(env_var, ptr);
		delete_env_var(head, new->key);
		add_front(head, new);
	}
}

t_env_var	*environ_to_linked_list_recursive(t_env_var *head, char **environ)
{
	char	*ptr;

	head = NULL;
	if (*environ != NULL)
	{
		ptr = ft_strchr(*environ, '=');
		if (ptr == NULL)
			head = environ_to_linked_list_recursive(head->next, environ + 1);
		else
		{
			head = assign_env_key_value(*environ, ptr);
			head->next = environ_to_linked_list_recursive(head->next, environ + 1);
		}
	}
	return (head);
}

void	setup(void)
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

	add_env_var(&head, cmds->args[1]);
	// put_env_vars(head);

	cr_assert_not_null(find_env_var(head, "jon"));
}

Test(export, delete, .init = setup)
{
	char		*input_str = "unset HOSTNAME";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	delete_env_var(&head, cmds->args[1]);
	// put_env_vars(head);

	cr_assert(zero(ptr,find_env_var(head, cmds->args[1])));
}

Test(export, overwrite, .init = setup)
{
	char		*input_str = "export PWD=KAWISH";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	char *value = find_env_var(head, "PWD")->value;
	cr_assert(eq(str, "/pwd/tests", value));

	add_env_var(&head, cmds->args[1]);
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

	add_env_var(&head, cmds->args[1]);
	char *value = find_env_var(head, "PWD")->value;
	put_env_vars(head);

	cr_assert(eq(str, "\0", value));
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
export_tests.c \
-lcriterion \
../src/parser/parser.c \
../src/parser/parser_utils.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
-L../src/libft -l:libft.a
*/