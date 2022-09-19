/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:09:33 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/09/19 16:11:22 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "structs.h"

enum {
	WORD,
	REDIRECT_OP,
	PIPE
};

bool	ft_isspace(int c);
bool	isspecialchar(char c);
void	print_tokens(t_token *head);
void	free_tokens(t_token *tokens);;
t_token	*tokenizer(char *str);
#endif
