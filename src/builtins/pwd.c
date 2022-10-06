/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:37:58 by ivork         #+#    #+#                 */
/*   Updated: 2022/10/06 14:25:20 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

extern int	g_exit_status;

/*
check for argument amounts ->> print error when to many arguments
*/
void	pwd_builtin(t_command *cmd, t_env_var **environ)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	ft_putendl_fd(working_dir, 1);
	free(working_dir);
	g_exit_status = 0;
}
