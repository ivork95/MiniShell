/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:22:11 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/10/19 04:38:05 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Private libaries */
# include "../src/libft/libft.h"
# include "tokenizer.h"
# include "structs.h"
# include "executor.h"
# include "heredoc.h"

/* Public libaries */
# include <stdio.h>
# include <stdlib.h>

/* free_breezy.c */
void		free_files(t_file *head);
void		free_commands(t_command *head);
void		free_splitted_array(char **splitted_array);

/* parser_utils_cont.c */
int			heredoc_setup(t_token *token, t_file *file, t_env_var **envp);
void		file_add_back(t_command **command, t_file *file);
char		*get_file_name(t_token *token, t_env_var *envp);

/* parser_utils.c */
int			redirect_type(char *str);
size_t		count_words(t_token *head);
t_command	*create_new_command(void);
void		command_add_back(t_command **head, t_command *new);

/* parser.c */
t_command	*parser(t_token *tokens, t_env_var **envp);

#endif