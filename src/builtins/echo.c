/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 01:34:55 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/23 10:13:40 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	write_args(t_command *command)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	if (command->args[1] && !ft_strncmp(command->args[1], "-n", 3))
	{
		new_line = 0;
		i++;
	}
	while (command->args[i])
	{
		write(1, command->args[i], ft_strlen(command->args[i]));
		if (command->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

static void	duplicate_stdout(t_file *files)
{
	int	fd;

	while (files)
	{
		if (files->type == REDIRECT_OUT || files->type == REDIRECT_APP)
		{
			if (files->type == REDIRECT_OUT)
				fd = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			else if (files->type == REDIRECT_APP)
				fd = open(files->file_name, O_WRONLY
						| O_CREAT | O_APPEND, 0664);
			if (fd == -1)
				perror("open");
			if (dup2(fd, STDOUT_FILENO) == -1)
				perror("dup2");
			if (close(fd) == -1)
				perror("close");
		}
		files = files->next;
	}
}

/*
should only work with option -n or no options
todo create error check for options 
*/
void	echo_builtin(t_command *command, t_env_var **environ)
{
	int	saved_stdout;

	(void)environ;
	saved_stdout = dup(1);
	if (command->files)
		duplicate_stdout(command->files);
	write_args(command);
	if (dup2(saved_stdout, 1) == -1)
		perror("dup2");
	if (close(saved_stdout) == -1)
		perror("close");
}
