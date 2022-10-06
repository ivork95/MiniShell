/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_cont.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 20:50:02 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/06 15:14:08 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*get_file_name(t_token *token)
{
	char	*file_name;

	file_name = malloc(sizeof(char) * token->len + 1);
	if (file_name == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	ft_strlcpy(file_name, token->str, token->len + 1);
	return (file_name);
}

void	file_add_back(t_command **command, t_file *file)
{
	t_file	*tmp;

	tmp = (*command)->files;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = file;
}

int	heredoc_setup(t_token *token, t_file *file, t_env_var **envp)
{
	file->file_name = create_file_name();
	if (token == NULL || heredoc_function(token, file->file_name, envp) == -1)
	{
		unlink(file->file_name);
		free(file->file_name);
		free(file);
		return (-1);
	}
	return (0);
}
