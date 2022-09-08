/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/08 17:14:23 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../includes/parser.h"
#include "../includes/expander.h"
#include "../includes/builtins.h"

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
	size_t i;

	i = 0;
	while (lookup_table[i].builtin_name)
	{
		if (!ft_strncmp(cmd->cmd, lookup_table[i].builtin_name, ft_strlen(cmd->cmd)))
		{
			lookup_table[i].function(cmd, head);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	handle_redirect_in(t_file *files)
{
	int	fd;

	while (files)
	{
		if (files->type == REDIRECT_OUT)
		{
			files = files->next;
			continue ;
		}
		else if (files->type == REDIRECT_IN)
			fd = open(files->file_name, O_RDONLY);
		if (fd == -1)
			ft_putendl_fd("Error: opening file", 2);
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_putendl_fd("Error: Could not duplicate fd", 2);
		if (close(fd) == -1)
			ft_putendl_fd("Error: could not close fd", 2);
		files = files->next;
	}
}

static void	handle_redirect_out(t_file *files)
{
	int	fd;

	while (files)
	{
		if (files->type == REDIRECT_IN)
		{
			files = files->next;
			continue ;
		}
		else if (files->type == REDIRECT_OUT)
			fd = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (files->type == REDIRECT_APP)
			fd = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
			ft_putendl_fd("Error: opening file", 2);
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_putendl_fd("Error: Could not duplicate fd", 2);
		if (close(fd) == -1)
			ft_putendl_fd("Error: could not close fd", 2);
		files = files->next;
	}
}

void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2])
{
	int fd_out;
	// handle first process
	//TODO add exec_builtin functin

	if (close(pipe_fd[0]) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (close(pipe_fd[1]) == -1)
		exit(EXIT_FAILURE);
	if (cmd->files != NULL)
	{
		// er is een redirect in/redirect out
		handle_redirect_in(cmd->files);
	}
	if (exec_builtin(head, cmd))
		exit(EXIT_SUCCESS);
	exec_ll(*head, cmd);
}

void	middle_process(t_env_var **head, t_command *cmd, int pipe_fd[2], int read_end)
{
	// handle middle process
	if (close(pipe_fd[0]) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1 || dup2(read_end, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (close(pipe_fd[1]) == -1)
		exit(EXIT_FAILURE);
	if (cmd->files != NULL)
	{
		handle_redirect_in(cmd->files);
		handle_redirect_out(cmd->files);
	}
	if (exec_builtin(head, cmd))
		exit(EXIT_SUCCESS);
	exec_ll(*head, cmd);
}

void	last_process(t_env_var **head, t_command *cmd, int read_end)
{
	// handle last process
	if (read_end != -1)
	{
		if (dup2(read_end, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (close(read_end) == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd->files != NULL)
	{
		// er is een redirect in/redirect out
		handle_redirect_in(cmd->files);
		handle_redirect_out(cmd->files);
	}
	if (exec_builtin(head, cmd))
		exit(EXIT_SUCCESS);
	exec_ll(*head, cmd);
}

void	executor(t_command *cmd, t_env_var **head)
{
	pid_t	w;
	pid_t	cpid;
	int 	pipe_fd[2];
	int 	read_end;
	size_t	i;

	i = 0;
	read_end = -1;

	if (cmd->next == NULL)
	{
		if (exec_builtin(head, cmd))
			return ;
	}
	while (cmd != NULL)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next != NULL) // Als er een volgend command is...
		{
			if (pipe(pipe_fd) == -1) // Maak pipe
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}

		cmd->cpid = fork();
		if (cmd->cpid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (cmd->cpid == 0) // Child
		{
			// hier moeten we pipe_fd meegeven
			if (cmd->next == NULL) // Als er een volgend command is...
				last_process(head, cmd, read_end);
			else if (i == 0)
				first_process(head, cmd, pipe_fd);
			else
				middle_process(head, cmd, pipe_fd, read_end);
		}
		else // Parent
		{
			//Check if closing pipes is needed
			// close(pipe_fd[0]);
			// w = waitpid(cmd->cpid, NULL, 0);
			// if (w == -1) {
			// 	perror("waitpid");
			// 	exit(EXIT_FAILURE);
			// }
			read_end = pipe_fd[0];
			// printf("read_end = %d\n",read_end);
			if (pipe_fd[1] != -1)
			{
				if (close(pipe_fd[1]) == -1)
				{
					perror("closeygf");
					exit(EXIT_FAILURE);
				}
			}
			i++;
			cmd = cmd->next;
		}
	}
	while (wait(NULL) != -1);
	// voor elke command creeer een nieuw process
	// tussen elke twee commands creer een pipe -> als er een cmd.next is maak een int pipe_fd[2] aan, of geef mee
	// als cmd.files niet null is -> dan moeten we redirecten
}

void	print_env(t_env_var *head)
{
	while (head != NULL)
	{
		ft_putstr_fd(head->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(head->value, 1);
		head = head->next;
	}
}

int	main(int argc, char **const argv, char **envp)
{
	t_command	*cmds;
	t_token		*tokens;
	t_env_var	*environ;
	char		*user_input;

	environ = environ_to_linked_list_recursive(environ, envp);
	while (1)
	{
		user_input = readline(">");
		tokens = tokenizer(user_input);
		if (tokens == NULL)
		{
			free(user_input);
			free_tokens(tokens);
			continue;
		}
		cmds = parser(tokens);
		expander(cmds, environ);
		executor(cmds, &environ);
		add_history(user_input);
		free(user_input);
		free_tokens(tokens);
		free_commands(cmds);
	}
	free_env_vars(environ);
	return (0);
}
