/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:17:30 by kawish        #+#    #+#                 */
/*   Updated: 2022/08/31 17:43:55 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	free_env_vars(t_env_var *head)
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

void	put_env_vars_declare(t_env_var *head)
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
			head->next = environ_to_linked_list_recursive(head->next,
					environ + 1);
		}
	}
	return (head);
}
