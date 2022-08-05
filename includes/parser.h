/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:22:11 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/05 12:05:45 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H


# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include "../src/libft/libft.h"
# include "tokenizer.h"

# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

typedef struct s_file
{
	enum type_t{
			REDIRECT_IN,
			REDIRECT_OUT,
			REDIRECT_APP,
	} type;
	char	*file_name;
}	t_file;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_file				*files;
	struct s_command	*next;
}	t_command;

int	closed_quotes(char *str);

char 	*handle_quotes(char **str_dup, char delimiter);
char 	*handle_spaces(char **str_dup);

t_command	*parser(t_token *tokens);

#endif