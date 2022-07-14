#ifndef MINISHELL_H
# define MINISHELL_H

# define COMMAND       0   // normal command
# define WORD          1   // normal word
# define REDIRECT_OP   2   // redirection operator (>, <, 2>)
# define PIPE          3   // `|` pipe operator

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_tokens
{
	char *str;
	size_t len;
	size_t type;
	bool quoted;
	struct s_tokens *next;

} t_tokens;

# endif
