/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 16:11:41 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 18:54:52 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"
#include "../../includes/builtins.h"
#include <unistd.h>
#include <stdio.h>

void change_directory(t_command *cmd, t_env_var *environ)
{
    char *old_pwd;
    
    old_pwd = getcwd(NULL, 0);
    if (!cmd->args[1])
    {
        if (chdir(getenv("HOME")) == -1)
		{
            printf("error\n");
			return ;
		}
    }
    else if(chdir(cmd->args[1]) == -1)
	{
        printf("error\n");
		return ;
	}
	// add_env_var(environ, "OLDPWD", old_pwd);
}