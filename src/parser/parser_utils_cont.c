/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_cont.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 20:50:02 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/27 12:36:12 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

extern int	g_exit_status;

char	*get_file_name(t_token *token, t_env_var *envp)
{
	char	*file_name;

	file_name = malloc(sizeof(char) * token->len + 1);
	if (file_name == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	ft_strlcpy(file_name, token->str, token->len + 1);
	if (ft_strchr(file_name, '$') != 0)
		expand_args(&file_name, 0, envp);
	if (ft_strlen(file_name) == 0 || only_quotes(file_name))
	{
		ft_putstr_fd("minishell: ", 1);
		write(1, token->str, token->len);
		ft_putendl_fd(": ambiguous redirect", 1);
		free(file_name);
		g_exit_status = 1;
		return (NULL);
	}
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

t_file	*create_file(void)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	file->next = NULL;
	return (file);
}
