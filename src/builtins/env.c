/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:17:30 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/09 19:16:25 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

t_env_var	*find_env_var(t_env_var *head, char *key_to_check)
{
	while (head != NULL)
	{
		if (!(ft_strncmp(head->key, key_to_check, ft_strlen(head->key))))
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
		ft_putstr_fd(vars->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(vars->value, 1);
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

t_env_var	*environ_to_linked_list_recursive(t_env_var *environ, char **envp)
{
	char	*p_equal_sign;

	environ = NULL;
	if (*envp != NULL)
	{
		p_equal_sign = ft_strchr(*envp, '=');
		if (p_equal_sign == NULL)
			environ = environ_to_linked_list_recursive(environ->next, envp + 1);
		else
		{
			environ = assign_env_key_value(*envp, p_equal_sign);
			environ->next = environ_to_linked_list_recursive(environ->next,
					envp + 1);
		}
	}
	return (environ);
}
