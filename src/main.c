/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:56:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/07/27 19:04:37 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../includes/parser.h"

void	print_commands(t_commands *cmds)
{
	size_t	i;

	i = 0;
	printf("--------------------\n");
	printf("command = %s\n", cmds->cmd);
	while (cmds->args && cmds->args[i] != NULL)
	{
		printf("args = %s\n", cmds->args[i]);
		i++;
	}
	if (cmds->files)
	{
		printf("file operattor = %d\nfile_name  = %s\n",
			cmds->files->type, cmds->files->file_name);
	}
	printf("--------------------\n");
}

int	main(void)
{
	t_commands	*cmds;
	t_tokens	*tokens;
	char		*user_input;

	user_input = readline(">");
	tokens = tokenizer(user_input);
	print_tokens(tokens);
	cmds = parser(tokens);
	print_commands(cmds);
	free(user_input);
	//todo free commands
	return (0);
}
