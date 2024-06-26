/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_breezy.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 12:32:27 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 12:32:40 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_files(t_file *head)
{
	if (head->next)
		free_files(head->next);
	free(head->file_name);
	free(head);
}

void	free_commands(t_command *head)
{
	size_t	i;

	if (head->next)
		free_commands(head->next);
	i = 0;
	while (head->args[i] != NULL)
	{
		free(head->args[i]);
		i++;
	}
	free(head->args);
	if (head->files)
		free_files(head->files);
	free(head);
}
