/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:24:29 by kawish        #+#    #+#                 */
/*   Updated: 2022/10/06 13:49:26 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

void	delete_env_var(t_env_var **head, t_env_var *prev, t_env_var *envp)
{
	if (!prev)
	{
		prev = *head;
		*head = envp->next;
	}
	else
	{
		prev->next = envp->next;
		prev = envp;
	}
	prev->next = NULL;
	free_env_vars(prev);
}

void	search_and_destroy(t_env_var **head, char *key)
{
	t_env_var	*prev;
	t_env_var	*envp;

	prev = NULL;
	envp = *head;
	while (envp)
	{
		if (!ft_strncmp(key, envp->key, ft_strlen(key)))
		{
			delete_env_var(head, prev, envp);
			return ;
		}
		prev = envp;
		envp = envp->next;
	}
}

void	unset_builtin(t_command *command, t_env_var **environ)
{
	size_t	i;

	i = 1;
	while (command->args[i])
	{
		search_and_destroy(environ, command->args[i]);
		i++;
	}
	g_exit_status = 0;
}
