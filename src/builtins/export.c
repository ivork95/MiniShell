/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:19:42 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/02 11:20:03 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

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

/* Wat er moet gebeuren bij return ;?*/
void	add_env_var(t_env_var **head, char *env_var)
{
	char		*ptr;
	t_env_var	*new;

	ptr = ft_strchr(env_var, '=');
	if (ptr == NULL)
		return ;
	else
	{
		new = assign_env_key_value(env_var, ptr);
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
