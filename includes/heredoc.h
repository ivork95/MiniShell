/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 08:03:50 by ivork         #+#    #+#                 */
/*   Updated: 2022/09/29 15:17:02 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

/* Public libraries */
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Private libraries */
# include "structs.h"
# include "minishell.h"
# include "executor.h"
# include "../src/libft/libft.h"

int		heredoc_function(t_token *token, char *file, t_env_var **envp);
char	*create_file_name(void);

#endif /* heredoc.h */
