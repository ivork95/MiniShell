#include <sys/wait.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/tokenizer.h"
#include "../includes/parser.h"
#include "../includes/builtins.h"

extern char	**environ;

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

// Test(execve_tests, foo)
// {
// 	char *input_str = "foo";

// 	t_token *tokens = tokenizer(input_str);
// 	t_command *commands = parser(tokens);
// 	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

// 	exec_ll(ll_environ, commands);
// }

// Test(execve_tests, foo_deleted_path)
// {
// 	char *input_str = "foo";

// 	t_token *tokens = tokenizer(input_str);
// 	t_command *commands = parser(tokens);
// 	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

// 	search_and_destroy(&ll_environ, "PATH");
// 	exec_ll(ll_environ, commands);
// }

// Test(execve_tests, path_ls)
// {
// 	char *input_str = "/bin/ls";

// 	t_token *tokens = tokenizer(input_str);
// 	t_command *commands = parser(tokens);
// 	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

// 	pid_t w;
// 	pid_t cpid = fork();
// 	if (cpid == -1) {
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (cpid == 0)
// 		exec_ll(ll_environ, commands);
// 	else
// 	{
// 		w = waitpid(cpid, NULL, 0);
// 		if (w == -1) {
// 			perror("waitpid");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	printf("Returned to parent function\n");
// }

// Test(execve_tests, path_ls_flags)
// {
// 	char *input_str = "/bin/ls -laF";

// 	t_token *tokens = tokenizer(input_str);
// 	t_command *commands = parser(tokens);
// 	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

// 	exec_ll(ll_environ, commands);
// }

// Test(execve_tests, path_ls_flags_seperate)
// {
// 	char *input_str = "/bin/ls -l -a -F";

// 	t_token *tokens = tokenizer(input_str);
// 	t_command *commands = parser(tokens);
// 	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

// 	exec_ll(ll_environ, commands);
// }

// Test(execve_tests, path_ls_flags_seperate)
// {
// 	char *input_str = "ls";

// 	t_token *tokens = tokenizer(input_str);
// 	t_command *commands = parser(tokens);
// 	t_env_var *ll_environ = environ_to_linked_list_recursive(ll_environ, environ);

// 	exec_ll(ll_environ, commands);
// }

/*
gcc \
execve_tests.c \
-lcriterion \
../src/parser/parser.c \
../src/parser/parser_utils.c \
../src/tokenizer/tokenizer.c \
../src/tokenizer/tokenizer_utils.c \
../src/builtins/env.c \
../src/builtins/export.c \
../src/builtins/unset.c \
../src/builtins/change_dir.c \
../src/builtins/echo.c \
../src/builtins/pwd.c \
../src/builtins/exit.c \
-L../src/libft -l:libft.a
*/