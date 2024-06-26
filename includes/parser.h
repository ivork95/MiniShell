/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:22:11 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/28 22:20:12 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include "../src/libft/libft.h"
# include "tokenizer.h"
# include "structs.h"


void		free_files(t_file *head);
void		free_commands(t_command *head);
int			redirect_type(char *str);
size_t		count_words(t_token *head);
t_command	*create_new_command(void);
void		command_add_back(t_command **head, t_command *new);
t_command	*parser(t_token *tokens);
void		print_commands(t_command *cmds);

#endif