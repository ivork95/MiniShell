#include "../../includes/structs.h"
#include "../libft/libft.h"

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