/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 13:50:39 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/23 14:33:15 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	perror_and_exit(char *s, int n)
{
	perror(s);
	exit(n);
}

void	print_commands(t_command *cmds)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (cmds)
	{
		i = 0;
		printf("--------------------\n");
		printf("cmds[%lu]\n", j);
		printf("command = %s\n", cmds->cmd);
		while (cmds->args && cmds->args[i])
		{
			printf("args[%lu] = %s\n", i, cmds->args[i]);
			i++;
		}
		while (cmds->files)
		{
			printf("file operattor = %d\nfile_name  = %s\n",
				cmds->files->type, cmds->files->file_name);
			cmds->files = cmds->files->next;
		}
		printf("--------------------\n");
		cmds = cmds->next;
		j++;
	}
}
