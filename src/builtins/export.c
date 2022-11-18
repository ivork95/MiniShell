/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:19:42 by kawish        #+#    #+#                 */
/*   Updated: 2022/11/18 13:10:28 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

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
	new->next = *head;
	*head = new;
}

static int	check_identifier(char *env_var)
{
	char	*ptr;

	ptr = ft_strchr(env_var, '=');
	if (ft_isdigit(env_var[0]))
		return (0);
	if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
		return (0);
	env_var++;
	while (*env_var && env_var != ptr)
	{
		if (!ft_isalnum(*env_var) && *env_var != '_')
		{
			if (ptr && *(ptr - 1) == '+' && (ptr - 1) == env_var)
				return (1);
			return (0);
		}
		env_var++;
	}
	return (1);
}

void	add_env_var(t_env_var **head, char *env_var)
{
	char		*ptr;
	t_env_var	*new;

	if (!check_identifier(env_var))
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd(env_var, STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		g_exit_status = 1;
		return ;
	}
	ptr = ft_strchr(env_var, '=');
	new = assign_env_key_value(env_var, ptr);
	if (ptr && *(ptr - 1) == '+')
		search_and_add(head, new);
	else
	{
		search_and_destroy(head, new->key);
		new->next = *head;
		*head = new;
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
