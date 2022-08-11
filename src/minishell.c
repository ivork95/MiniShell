/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/11 16:32:52 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/parser.h"

void	print_commands(t_command *cmds)
{
	size_t	i;

	while (cmds)
	{
		i = 0;
		printf("--------------------\n");
		printf("command = %s\n", cmds->cmd);
		while (cmds->args && cmds->args[i])
		{
			printf("args = %s\n", cmds->args[i]);
			i++;
		}
		while (cmds->files)
		{
			printf("file operattor = %d\nfile_name  = %s\n",
				cmds->files->type, cmds->files->file_name);
			cmds->files = cmds->files->next;
		}
		printf("--------------------\n");
		cmds = cmds->next;
	}
}

void	err_func(char *str, int code)
{
	perror(str);
	exit(code);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	return ;
}

char	*get_path(char **arguments, char *cmd)
{
	char	*path;
	char	*full_path;
	int		i;

	while (*arguments)
	{
		if (ft_strncmp(*arguments, "PATH=", 5) == 0)
			path = ft_strdup(*arguments);
		arguments++;
	}
	arguments = ft_split(path, ':');
	free(path);
	i = 0;
	path = ft_strjoin("/", cmd);
	while (arguments[i])
	{
		full_path = ft_strjoin(arguments[i], path);
		if (access(full_path, F_OK) == 0)
			break ;
		free(full_path);
		i++;
	}
	free_array(arguments);
	free(path);
	return (full_path);
}

void execute_command(t_command *cmd, char **envp)
{
	char *path;

	path = get_path(envp, cmd->cmd);
	printf("path = %s\n", path);
	execve(path, cmd->args, envp);
}

int	main(int argc, char **const argv, char **envp)
{
	t_command	*cmds;
	t_token	*tokens;
	char		*user_input;

	user_input = readline(">");
	tokens = tokenizer(user_input);
	
	print_tokens(tokens);
	
	cmds = parser(tokens);
	print_commands(cmds);

	free(user_input);
	free_tokens(tokens);
	free_commands(cmds);
	
	execute_command(cmds, envp);
	return (0);
}
