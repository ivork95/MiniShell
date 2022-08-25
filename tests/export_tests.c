#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/libft/libft.h"

extern char	**environ;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

static unsigned int count_environ_vars(char **environ)
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

static unsigned int count_env_vars(t_env_var *head)
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

void	put_env_vars(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->value, 1);
		head = head->next;
	}
}

void	free_env_vars(t_env_var *head)
{
	if (head->next)
		free_env_vars(head->next);
	free(head->key);
	free(head->value);
	free(head);
}

void delete_env_var(t_env_var **head, char *key)
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

t_env_var	*create_new_env_var(char *key, char *value)
{
	t_env_var	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->key = ft_strdup(key);
	if (node->key == NULL)
		exit(EXIT_FAILURE);
	node->value = ft_strdup(value);
	if (node->value == NULL)
		exit(EXIT_FAILURE);
	node->next = NULL;
	return (node);
}

t_env_var *find_env_var(t_env_var *head, char *key_to_check)
{
	while (head != NULL)
	{
		if (!(ft_strncmp(head->key, key_to_check, ft_strlen(head->key))))
			return (head);
		head = head->next;
	}
	return (head);
}

void add_env_var(t_env_var **head, char *key, char *value)
{
	t_env_var	*new;

	if (find_env_var(*head, key))
		delete_env_var(head, key);
	new = create_new_env_var(key, value);
	new->next = *head;
	*head = new;
}

void	assign_env_key_value(t_env_var *head, char *env_var)
{
	char		*ptr;
	size_t		len_val;
	ptrdiff_t	len_key;

	ptr = ft_strchr(env_var, '=');
	len_key = (ptr - env_var) + 1;
	head->key = malloc(sizeof(*(head->key)) * len_key);
	if (head->key == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(head->key, env_var, len_key);
	ptr = ptr + 1;
	len_val = ft_strlen(ptr) + 1;
	head->value = malloc(sizeof(*(head->value)) * len_val);
	if (head->value == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(head->value, ptr, len_val);
}

t_env_var	*environ_to_linked_list_recursive(t_env_var *head, char **environ)
{
	head = NULL;
	if (*environ != NULL)
	{
		head = malloc(sizeof(*head));
		if (head == NULL)
			exit(EXIT_FAILURE);
		assign_env_key_value(head, *environ);
		head->next = environ_to_linked_list_recursive(head->next, environ + 1);
	}
	return (head);
}

Test(export, is_copied)
{
	t_env_var		*head;
	unsigned int	ll_count;
	unsigned int	actual_count;
	unsigned int	i;
	char			*tmp_str;
	char			*joined_str;

	head = environ_to_linked_list_recursive(head, environ);

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

Test(export, add)
{
	t_env_var	*head;
	t_env_var	*new;
	char		*key_to_add = "jon";

	head = environ_to_linked_list_recursive(head, environ);
	add_env_var(&head, key_to_add, "aegon");

	// put_env_vars(head);
	cr_assert_not_null(find_env_var(head, key_to_add));
}

Test(export, delete)
{
	t_env_var	*head;
	char		*key_to_delete = "HOSTNAME";

	head = environ_to_linked_list_recursive(head, environ);
	delete_env_var(&head, key_to_delete);

	// put_env_vars(head);
	cr_assert(zero(ptr,find_env_var(head, key_to_delete)));
}

Test(export, overwrite)
{
	t_env_var	*head;
	char		*value;
	char		*key_to_overwrite = "HOSTNAME";
	char		*value_to_overwrite = "KAWISH";

	head = environ_to_linked_list_recursive(head, environ);
	add_env_var(&head, key_to_overwrite,value_to_overwrite);
	value = find_env_var(head, key_to_overwrite)->value;
	// put_env_vars(head);
	cr_assert(eq(str, value_to_overwrite, value));
}

Test(export, overwrite_empty_val)
{
	t_env_var	*head;
	char		*value;
	char		*key_to_overwrite = "HOSTNAME";
	char		*value_to_overwrite = "\0";

	head = environ_to_linked_list_recursive(head, environ);
	add_env_var(&head, key_to_overwrite,value_to_overwrite);
	value = find_env_var(head, key_to_overwrite)->value;
	put_env_vars(head);
	cr_assert(eq(str, value_to_overwrite, value));
}