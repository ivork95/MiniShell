/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 01:34:55 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/18 01:34:56 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include <unistd.h>
#include <fcntl.h>

void	write_args(t_command *command)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (command->args[i])
	{
		if (!ft_strncmp(command->args[1], "-n", 3) && new_line)
		{
			new_line = 0;
			i++;
		}
		write(1, command->args[i], ft_strlen(command->args[i]));
		if (command->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

void	duplicate_fd(t_file *files)
{
	int	fd;

	while (files)
	{
		if (files->type == REDIRECT_OUT)
		{
			fd = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (fd == -1)
				printf("Error opening file\n");
		}
		else if (files->type == REDIRECT_APP)
		{
			fd = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (fd == -1)
				printf("Error opening file\n");
		}
		else
			files = files->next;
		if (dup2(fd, STDOUT_FILENO) == -1)
			printf("Could not duplicate fd\n");
		if (close(fd) == -1)
			printf("COuld not close fd\n");
		files = files->next;
	}
}

void	echo_builtin(t_command *command)
{
	if (command->files)
		duplicate_fd(command->files);
	write_args(command);
}
