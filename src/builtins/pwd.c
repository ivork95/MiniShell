/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:37:58 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/02 11:20:35 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/structs.h"
#include "../libft/libft.h"

/*
check for argument amounts ->> print error when to many arguments
*/
void	pwd_builtin(__attribute__ ((unused)) t_command *cmd,
	__attribute__ ((unused)) t_env_var **environ)
{
	char	*working_dir;

	working_dir = getcwd(NULL, 0);
	ft_putendl_fd(working_dir, 1);
	free(working_dir);
}
