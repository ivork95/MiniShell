/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 16:07:48 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/24 16:07:49 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <unistd.h>
#include <stdio.h>

void change_directory(t_command *cmd)
{
    char *old_pwd;
    
    old_pwd = getcwd(NULL, 0);
    if (!cmd->args[1])
    {
        if (chdir(getenv("HOME")) == -1)
            printf("error\n");
    }
    else if(chdir(cmd->args[1]) == -1)
        printf("error\n");
}