/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 10:44:53 by kawish        #+#    #+#                 */
/*   Updated: 2022/09/14 12:57:18 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* Private libraries */
# include "../src/libft/libft.h"
# include "structs.h"
# include "builtins.h"

/* Public libraries */
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

void	exec_ll(t_env_var *ll_environ, t_command *command);
int		exec_builtin(t_env_var **head, t_command *cmd);
void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2]);
void	middle_process(t_env_var **head,
			t_command *cmd, int pipe_fd[2], int read_end);
void	last_process(t_env_var **environ, t_command *cmd, int read_end);
void	executor(t_command *commands, t_env_var **environ);

#endif