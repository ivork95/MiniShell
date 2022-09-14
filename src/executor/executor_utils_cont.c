/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils_cont.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 12:50:29 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/14 12:58:53 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static void	free_splitted_array(char **splitted_array)
{
	int	i;

	i = 0;
	while (splitted_array[i] != NULL)
	{
		free(splitted_array[i]);
		i++;
	}
	free(splitted_array);
}

char	*get_full_path(char *path, const char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	*cmd_dup;

	i = 0;
	paths = ft_split(path, ':');
	cmd_dup = ft_strjoin("/", cmd);
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], cmd_dup);
		if (!access(full_path, X_OK))
			break ;
		free(full_path);
		i++;
	}
	free(cmd_dup);
	if (paths[i] == NULL)
	{
		free_splitted_array(paths);
		printf("minishell: %s: command not found\n", cmd);
		exit(EXIT_FAILURE);
	}
	free_splitted_array(paths);
	return (full_path);
}

void	exec_ll(t_env_var *ll_environ, t_command *command)
{
	t_env_var	*path_node;
	char		*path;
	char		*full_path;

	path_node = find_env_var(ll_environ, "PATH");
	if (path_node == NULL)
	{
		printf("minishell: %s: No such file or directory\n", command->args[0]);
		exit(EXIT_FAILURE);
	}
	path = path_node->value;
	if (access(command->args[0], X_OK) == 0)
		full_path = command->args[0];
	else
		full_path = get_full_path(path, command->args[0]);
	execve(full_path, command->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	exec_builtin(t_env_var **head, t_command *cmd)
{
	size_t	i;

	i = 0;
	while (lookup_table[i].builtin_name)
	{
		if (!ft_strncmp(cmd->cmd,
				lookup_table[i].builtin_name, ft_strlen(cmd->cmd)))
		{
			lookup_table[i].function(cmd, head);
			return (1);
		}
		i++;
	}
	return (0);
}
