/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:09:33 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/08/24 17:04:36 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include "../src/libft/libft.h"

enum {
	WORD,
	REDIRECT_OP,
	PIPE
};

typedef struct s_token
{
	char			*str;
	size_t			len;
	size_t			type;
	bool			quoted;
	struct s_token	*next;

}	t_token;

bool	ft_isspace(int c);
bool	isspecialchar(char c);
void	print_tokens(t_token *head);
void	free_tokens(t_token * tokens);;
t_token	*tokenizer(char *str);
#endif
