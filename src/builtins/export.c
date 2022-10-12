/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:19:42 by kawish        #+#    #+#                 */
/*   Updated: 2022/10/12 03:32:01 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

static void	add_front(t_env_var **lst, t_env_var *new)
{
	new->next = *lst;
	*lst = new;
}

t_env_var	*assign_env_key_value(char *env_var, char *ptr)
{
	t_env_var	*head;
	ptrdiff_t	len_key;

	head = malloc(sizeof(*head));
	if (head == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	head->value = NULL;
	head->next = NULL;
	if (ptr)
	{
		len_key = (ptr - env_var);
		if (*(ptr - 1) == '+')
			len_key -= 1;
	}
	else
		len_key = ft_strlen(env_var);
	head->key = ft_substr(env_var, 0, len_key);
	if (head->key == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	if (!ptr)
		return (head);
	head->value = ft_substr(env_var, ptr - env_var + 1, ft_strlen(ptr));
	if (head->value == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	return (head);
}

void	search_and_add(t_env_var **head, t_env_var *new)
{
	t_env_var	*envp;
	char		*new_str;

	envp = *head;
	while (envp)
	{
		if (!ft_strncmp(envp->key, new->key, ft_strlen(new->key)))
		{
			new_str = ft_strjoin(envp->value, new->value);
			free(envp->value);
			free_env_vars(new);
			envp->value = new_str;
			return ;
		}
		envp = envp->next;
	}
	add_front(head, new);
}

void	add_env_var(t_env_var **head, char *env_var)
{
	char		*ptr;
	t_env_var	*new;

	if (!ft_isalnum(*env_var))
	{
		printf("minishell: export: %s: not a valid identifier\n", env_var);
		exit(EXIT_FAILURE);
	}
	ptr = ft_strchr(env_var, '=');
	new = assign_env_key_value(env_var, ptr);
	if (*(ptr - 1) == '+')
		search_and_add(head, new);
	else
	{
		search_and_destroy(head, new->key);
		add_front(head, new);
	}
}

void	export_builtin(t_command *command, t_env_var **environ)
{
	size_t	i;

	i = 0;
	while (command->args[i] != NULL)
		i++;
	if (i == 1)
		put_env_vars_declare(*environ);
	i = 1;
	while (command->args[i] != NULL)
	{
		add_env_var(environ, command->args[i]);
		i++;
	}
}
