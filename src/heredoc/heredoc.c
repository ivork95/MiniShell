/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 14:39:43 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/10/19 15:34:35 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/heredoc.h"

char	*create_file_name(void)
{
	int		n;
	char	*file_name;
	char	*file_num;

	n = 0;
	while (n < INT_MAX)
	{
		file_num = ft_itoa(n);
		if (file_num == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
		file_name = ft_strjoin("tmp", file_num);
		if (file_name == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
		free(file_num);
		if (access(file_name, F_OK))
			return (file_name);
		free(file_name);
		n++;
	}
	return (NULL);
}

static void	get_user_intput(char *file_name, char *delimiter, t_env_var *envp)
{
	char	*input;
	int		fd;

	fd = open(file_name, O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		perror_and_exit("fd", EXIT_FAILURE);
	while (1)
	{
		input = readline("heredoc>");
		if (!input)
			perror_and_exit("warning: here-doc delimited by EOF", EXIT_SUCCESS);
		if (!ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1))
			break ;
		if (ft_strchr(input, '$') != 0)
            expand_args(&input, 0, envp);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	close(fd);
}

static char	*copy_delimiter(t_token *token)
{
	char	*delimiter;

	delimiter = malloc(sizeof(char) * token->len + 1);
	if (delimiter == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	ft_strlcpy(delimiter, token->str, token->len + 1);
	return (delimiter);
}

int	heredoc_function(t_token *token, char *file_name, t_env_var **envp)
{
	char				*delimiter;
	int					status;
	pid_t				pid;
	struct sigaction	sa;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		init_signals(&sa, sigint_heredoc_handler);
		delimiter = copy_delimiter(token);
		get_user_intput(file_name, delimiter, *envp);
		free(delimiter);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &status, 0) == -1)
		perror_and_exit("waitpid", EXIT_FAILURE);
	set_exit_status(status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (-1);
	return (0);
}
