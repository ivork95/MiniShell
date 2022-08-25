/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:22:11 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/25 15:19:39 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../src/libft/libft.h"
#include "tokenizer.h"

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;


typedef struct s_file
{
	enum type_t{
			REDIRECT_IN,
			REDIRECT_OUT,
			REDIRECT_APP,
	} type;
	char			*file_name;
	struct s_file	*next;
}	t_file;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_file				*files;
	t_env_var			**env_vars;
	struct s_command	*next;
}	t_command;

void		free_files(t_file *head);
void		free_commands(t_command *head);
int			redirect_type(char *str);
size_t		count_words(t_token *head);
t_command	*create_new_command(t_env_var **envp);
void		command_add_back(t_command **head, t_command *new);
t_command	*parser(t_token *tokens, t_env_var **envp);

// int		closed_quotes(char *str);
// char	*handle_quotes(char **str_dup, char delimiter);
// char	*handle_spaces(char **str_dup);

#endif