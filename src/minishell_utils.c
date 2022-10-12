/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 13:50:39 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/10/12 16:51:26 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

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

int	parser_and_expander(t_command **cmds, t_token *tokens,
				t_env_var **environ, char *user_input)
{
	*cmds = parser(tokens, environ);
	if (*cmds == NULL || (*cmds)->cmd == NULL)
	{
		if (*cmds)
			unlink((*cmds)->files->file_name);
		free(user_input);
		free_tokens(tokens);
		free_commands(*cmds);
		return (1);
	}
	expander(*cmds, *environ);
	if ((*cmds)->cmd[0] == 0)
	{
		free(user_input);
		free_tokens(tokens);
		free_commands(*cmds);
		return (1);
	}
	return (0);
}

int	syntax_protector(t_token *token)
{
	if(!token)
		return (0);
	while (token)
	{
		if (token->type == REDIRECT_OP && (!token->next || token->next->type != WORD))
		{
			ft_putendl_fd("minishell: syntax error", 1);
			g_exit_status = 2;
			return (0);
		}
		if (token->type == PIPE && token->next && token->next->type == PIPE)
		{
			ft_putendl_fd("minishell: syntax error", 1);
			g_exit_status = 2;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
