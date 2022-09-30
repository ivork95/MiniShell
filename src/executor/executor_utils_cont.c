/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils_cont.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 10:53:02 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/30 14:12:14 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

extern int	g_exit_status;

void	set_exit_status(int last_exit_status)
{
	if (WIFEXITED(last_exit_status))
		g_exit_status = WEXITSTATUS(last_exit_status);
}

void	open_dup_close_guards(int fd)
{
	if (fd == -1)
		perror_and_exit("open", EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		perror_and_exit("dup2", EXIT_FAILURE);
	if (close(fd) == -1)
		perror_and_exit("close", EXIT_FAILURE);
}

char *env_var_to_str(t_env_var *node)
{
	char	*env_var_str;
	char	*tmp;

	tmp = ft_strjoin(node->key, "=");
	if (tmp == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	env_var_str = ft_strjoin(tmp, node->value);
	if (env_var_str == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	free(tmp);
	return (env_var_str);
}

char **calloc_two_d_env(t_env_var *environ)
{
	unsigned int	n;
	char			**two_d_env;

	n = 0;
	while (environ)
	{
		n++;
		environ = environ->next;
	}
	two_d_env = ft_calloc(n + 1, sizeof(*two_d_env));
	if (two_d_env == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	return (two_d_env);
}

char **llenv_to_two_d_env(t_env_var *environ)
{
	unsigned int	n;
	char			**two_d_env;

	n = 0;
	two_d_env = calloc_two_d_env(environ);
	while (environ)
	{
		two_d_env[n] = env_var_to_str(environ);
		n++;
		environ = environ->next;
	}
	return (two_d_env);
}
