/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 14:39:43 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/23 14:43:16 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/heredoc.h"

void	heredoc_function(t_token *token)
{
	char	*user_input;
	char	*joined_str;
	char	*delimiter;
	int		fd;

	delimiter = malloc(sizeof(char) * token->len + 1);
	if (delimiter == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	ft_strlcpy(delimiter, token->str, token->len + 1);
	fd = open("tmp", O_RDWR | O_CREAT, 0664);
	if (fd == -1)
		perror_and_exit("fd", EXIT_FAILURE);
	while (1)
	{
		user_input = readline("heredoc>");
		if (!ft_strncmp(user_input, delimiter, ft_strlen(delimiter) + 1))
			break ;
		joined_str = ft_strjoin(user_input, "\n");
		if (joined_str == NULL)
			perror_and_exit("malloc", EXIT_FAILURE);
		write(fd, joined_str, ft_strlen(joined_str));
		free(user_input);
		free(joined_str);
	}
	close(fd);
}
