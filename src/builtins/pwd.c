/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:37:58 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/27 01:52:06 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/structs.h"

void	print_current_directory(t_command *cmd, t_env_var **environ)
{
	//check for argument amounts ->> print error when to many arguments
	char	*working_dir;

	environ = NULL;
	working_dir = getcwd(NULL, 0);
	write(1, working_dir, strlen(working_dir));
	write(1, "\n", 1);
	free(working_dir);
}
