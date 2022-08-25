/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/25 15:57:49 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/expander.h"
#include "../includes/builtins.h"

void	print_commands(t_command *cmds)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (cmds)
	{
		i = 0;
		printf("--------------------\n");
		printf("cmds[%lu]\n", j);
		printf("command = %s\n", cmds->cmd);
		while (cmds->args && cmds->args[i])
		{
			printf("args[%lu] = %s\n", i, cmds->args[i]);
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
		j++;
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
	// char *path;
	const char *builtins[6] = {"echo",
            "pwd",
            "cd",
            "env",
            "unset",
            "export"};

	void (*builtin_func[5])() = {
                                echo_builtin,
                                print_current_directory,
                                change_directory,
								print_env_vars,
								delete_env_var};
    for (int i = 0; i < 5; i++)
    {
        if (!ft_strncmp(builtins[i], cmd->cmd, ft_strlen(cmd->cmd) + 1))
            builtin_func[i](cmd);
    }
	// path = get_path(envp, cmd->cmd);
	// printf("path = %s\n", path);
	// execve(path, cmd->args, envp);
}

int	main(int argc, char **const argv, char **envp)
{
	t_command	*cmds;
	t_token		*tokens;
	t_env_var	*environ;
	
	char		*user_input;
	environ = environ_to_linked_list_recursive(environ, envp);
	// user_input = readline(">");
	tokens = tokenizer("unset HOSTNAME");
	
	print_tokens(tokens);
	
	cmds = parser(tokens, &environ);
	expander(cmds, envp);
	// print_commands(cmds);

	// free(user_input);
	// free_tokens(tokens);
	// free_commands(cmds);
	print_env_vars(cmds);
	execute_command(cmds, envp);
	printf("-----------------------------------\n");
	print_env_vars(cmds);
	return (0);
}
