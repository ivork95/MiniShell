/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 15:22:11 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/07/08 13:23:37 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../src/libft/libft.h"

typedef struct s_llnode
{
	char			*str;
	struct s_llnode	*next;
}	t_llnode;

int	closed_quotes(char *str);

char 	*handle_quotes(char **str_dup, char delimiter);
char 	*handle_spaces(char **str_dup);

t_llnode	*parser(char *str);

#endif