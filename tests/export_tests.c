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

void	deze_functie_word_niet_eens_gecalled_zn_moer(void)
{
	ft_strlcpy(NULL, NULL, 0); // deze functie is heilig ah mattie
}

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
	if (head->next)
		free_env_vars(head->next);
	free(head->key);
	free(head->value);
	free(head);
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

Test(export, nieuw, .init = setup)
{
	char		*input_str = "export jon=aegon";
	t_token		*tokens = tokenizer(input_str);
	t_command	*cmds = parser(tokens);

	add_env_var(&head, cmds->args[1]);
	// put_env_vars(head);

	cr_assert_not_null(find_env_var(head, "jon"));

	free_env_vars(head);
}

// Test(export, is_copied, .init = setup)
// {
// 	unsigned int	ll_count;
// 	unsigned int	actual_count;
// 	unsigned int	i;
// 	char			*tmp_str;
// 	char			*joined_str;

// 	ll_count = count_env_vars(head);
// 	actual_count = count_environ_vars(environ);
// 	cr_assert(eq(int, actual_count, ll_count));

// 	i = 0;
// 	while (i < actual_count)
// 	{
// 		tmp_str = ft_strjoin(head->key, "=");
// 		joined_str = ft_strjoin(tmp_str, head->value);
// 		free(tmp_str);
// 		cr_assert_not(ft_strncmp(environ[i], joined_str, ft_strlen(environ[i])));
// 		free(joined_str);
// 		head = head->next;
// 		i++;
// 	}
// }

// Test(export, add, .init = setup)
// {
// 	t_env_var	*new;
// 	char		*key_to_add = "jon";

// 	add_env_var(&head, key_to_add, "aegon");

// 	put_env_vars(head);
// 	cr_assert_not_null(find_env_var(head, key_to_add));
// }

// Test(export, delete, .init = setup)
// {
// 	char		*key_to_delete = "HOSTNAME";

// 	delete_env_var(&head, key_to_delete);

// 	// put_env_vars(head);
// 	cr_assert(zero(ptr,find_env_var(head, key_to_delete)));
// }

// Test(export, overwrite, .init = setup)
// {
// 	char		*value;
// 	char		*key_to_overwrite = "PWD";
// 	char		*value_to_overwrite = "KAWISH";

// 	value = find_env_var(head, key_to_overwrite)->value;
// 	cr_assert(eq(str, "/pwd/tests", value));

// 	add_env_var(&head, key_to_overwrite, value_to_overwrite);
// 	value = find_env_var(head, key_to_overwrite)->value;
// 	// put_env_vars(head);
// 	cr_assert(eq(str, value_to_overwrite, value));
// }

// Test(export, overwrite_empty_val, .init = setup)
// {
// 	char		*value;
// 	char		*key_to_overwrite = "HOSTNAME";
// 	char		*value_to_overwrite = "\0";

// 	add_env_var(&head, key_to_overwrite,value_to_overwrite);
// 	value = find_env_var(head, key_to_overwrite)->value;
// 	// put_env_vars(head);
// 	cr_assert(eq(str, value_to_overwrite, value));
// }

// Test(export, export_without_args, .init = setup)
// {
// 	put_env_vars_declare(head);
// }

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