#ifndef HEREDOC_H
# define HEREDOC_H

/* Public libraries */
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Private libraries */
# include "structs.h"
# include "minishell.h"
# include "../src/libft/libft.h"

void	heredoc_function(t_token *token);

#endif /* heredoc.h */