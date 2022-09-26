/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:17:49 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/26 16:10:16 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	create_processes_inner(int *read_end, int *pipe_fd)
{
	*read_end = pipe_fd[0];
	close_pipe(pipe_fd[1]);
	free(pipe_fd);
}

int	*create_pipe(void)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (pipe(pipe_fd) == -1)
		perror_and_exit("pipe", EXIT_FAILURE);
	return (pipe_fd);
}

void	close_pipe(int pipe_fd)
{
	if (close(pipe_fd) == -1)
		perror_and_exit("close", EXIT_FAILURE);
}

char	*get_full_path_inner(char **paths, char *cmd_dup, const char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], cmd_dup);
		if (full_path == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
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

char	*get_full_path(char *path, const char *cmd)
{
	char	**paths;
	char	*cmd_dup;

	paths = ft_split(path, ':');
	if (paths == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	cmd_dup = ft_strjoin("/", cmd);
	if (cmd_dup == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	return (get_full_path_inner(paths, cmd_dup, cmd));
}
