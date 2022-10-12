/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:37:58 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/12 20:25:30 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

void	pwd_builtin(t_command *cmd, t_env_var **environ)
{
	char	*working_dir;

	(void)cmd;
	(void)environ;
	working_dir = getcwd(NULL, 0);
	ft_putendl_fd(working_dir, STDOUT_FILENO);
	free(working_dir);
	g_exit_status = 0;
}
