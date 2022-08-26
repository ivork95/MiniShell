/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 13:27:42 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/26 15:54:15 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include <stdbool.h>

typedef enum t_redirect{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APP
}	t_redirect;

typedef struct s_env_var
{
	char				*env_var;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_token
{
	char			*str;
	size_t			len;
	size_t			type;
	bool			quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	t_redirect		type;
	char			*file_name;
	struct s_file	*next;
}	t_file;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_file				*files;
	struct s_command	*next;
}	t_command;

typedef struct s_builtins
{
	char	*builtin_name;
	void	(*function)(t_command *command, char **envp);
} t_builtins;

#endif
