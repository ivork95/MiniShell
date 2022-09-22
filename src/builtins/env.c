/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:17:30 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/22 16:04:24 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

t_env_var	*find_env_var(t_env_var *head, char *key_to_check)
{
	while (head != NULL)
	{
		if (!(ft_strncmp(head->key, key_to_check, ft_strlen(key_to_check))))
			return (head);
		head = head->next;
	}
	return (head);
}

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

void	env(__attribute__ ((unused)) t_command *command, t_env_var **head)
{
	t_env_var	*vars;

	vars = *head;
	while (vars != NULL)
	{
		if (ft_strncmp(vars->key, "?", 2))
		{
			ft_putstr_fd(vars->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(vars->value, 1);
		}
		vars = vars->next;
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
	add_env_var(&head, "?=0");
	return (head);
}
