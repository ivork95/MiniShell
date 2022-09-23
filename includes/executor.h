/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:59:40 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/23 10:34:46 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* Private libraries */
# include "structs.h"
# include "expander.h"
# include "builtins.h"
# include "parser.h"

/* Public libraries */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

/* executor.c */
void	executor(t_command *cmd, t_env_var **head);
void	exec_ll(t_env_var *ll_environ, t_command *command);
int		exec_builtin(t_env_var **head, t_command *cmd);

/* executor_utils.c */
void	error_handeling(char *str);
int		*create_pipe(void);
void	close_pipe(int pipe_fd);
char	*get_full_path(char *path, const char *cmd);

/* processes.c */
void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2]);
void	middle_process(t_env_var **head, t_command *cmd, int pipe_fd[2],
			int read_end);
void	last_process(t_env_var **head, t_command *cmd, int read_end);

#endif
