/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:59:40 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/15 21:00:37 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

void	executor(t_command *cmd, t_env_var **head);
void	last_process(t_env_var **head, t_command *cmd, int read_end);
void	middle_process(t_env_var **head, t_command *cmd, int pipe_fd[2],
			int read_end);
void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2]);
void	exec_ll(t_env_var *ll_environ, t_command *command);
void	error_handeling(char *str);
void	close_pipe(int pipe_fd);
char	*get_full_path(char *path, const char *cmd);
int		exec_builtin(t_env_var **head, t_command *cmd);
int		*create_pipe(void);

#endif
