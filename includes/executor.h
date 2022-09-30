/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:59:40 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/30 11:13:42 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/* Private libraries */
# include "structs.h"
# include "expander.h"
# include "builtins.h"
# include "parser.h"
# include "minishell.h"
# include "signals.h"

/* Public libraries */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>

/* executor.c */
void	set_exit_status(int last_exit_status);
void	executor(t_command *cmd, t_env_var **head);
void	exec_ll(t_env_var *ll_environ, t_command *command);
int		exec_builtin(t_env_var **head, t_command *cmd);

/* executor_utils.c */
int		*create_pipe(void);
void	close_pipe(int pipe_fd);
char	*get_full_path(char *path, const char *cmd);
void	copy_read_end(int *read_end, int *pipe_fd);

/* executor_utils_cont.c */
void open_dup_close_guards(int fd);

/* processes.c */
void	first_process(t_env_var **head, t_command *cmd, int pipe_fd[2]);
void	middle_process(t_env_var **head, t_command *cmd, int pipe_fd[2],
			int read_end);
void	last_process(t_env_var **head, t_command *cmd, int read_end);

#endif
