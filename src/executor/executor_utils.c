/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:17:49 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/15 15:33:53 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/builtins.h"

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