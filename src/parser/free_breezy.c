/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_breezy.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:32:27 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/28 22:38:54 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// void	free_files(t_file *head)
// {
// 	if (head->next)
// 		free_files(head->next);
// 	free(head->file_name);
// 	free(head);
// }

// void	free_commands(t_command *head)
// {
// 	size_t	i;

// 	if (head->next)
// 		free_commands(head->next);
// 	i = 0;
// 	while (head->args[i] != NULL)
// 	{
// 		free(head->args[i]);
// 		i++;
// 	}
// 	free(head->args);
// 	if (head->files)
// 		free_files(head->files);
// 	free(head);
// }

void	free_files(t_file *head)
{
	t_file	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_args(char **args)
{
	unsigned int	i;

	i = 1;
	if (!args)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_commands(t_command *head)
{
	t_command	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		free_args(tmp->args);
		free_files(tmp->files);
		free(tmp);
	}
}

void	free_splitted_array(char **splitted_array)
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
