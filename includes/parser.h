/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:22:11 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/04 13:09:02 by ivork         ########   odam.nl         */
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

typedef struct s_files
{
	enum type_t{
			REDIRECT_IN,
			REDIRECT_OUT,
			REDIRECT_APP,
	} type;
	char	*file_name;
}	t_files;

typedef struct s_commands
{
	char				*cmd;
	char				**args;
	t_files				*files;
	struct s_commands	*next;
}	t_commands;

int	closed_quotes(char *str);

char 	*handle_quotes(char **str_dup, char delimiter);
char 	*handle_spaces(char **str_dup);

t_commands	*parser(t_tokens *tokens);

#endif