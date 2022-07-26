/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/21 11:09:33 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/07/21 18:20:34 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COMMAND       0   // normal command
# define WORD          1   // normal word
# define REDIRECT_OP   2   // redirection operator (>, <, 2>)
# define PIPE          3   // `|` pipe operator

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include "../src/libft/libft.h"

typedef struct s_tokens
{
	char			*str;
	size_t			len;
	size_t			type;
	bool			quoted;
	struct s_tokens	*next;

}	t_tokens;

bool	ft_isspace(int c);
bool	isspecialchar(char c);
void	print_tokens(t_tokens *head);
t_tokens	*tokenizer(char *str);
#endif
