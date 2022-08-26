/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:37:58 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 12:51:35 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	print_current_directory(void)
{
	char	*working_dir;
	size_t	len;

	working_dir = getcwd(NULL, 0);
	write(1, working_dir, strlen(working_dir));
	free(working_dir);
}
