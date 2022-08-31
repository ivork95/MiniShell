/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:24:29 by kawish        #+#    #+#                 */
/*   Updated: 2022/08/31 17:44:08 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	delete_env_var(t_env_var **head, char *key)
{
	t_env_var	*tmp;
	t_env_var	*envp;

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
