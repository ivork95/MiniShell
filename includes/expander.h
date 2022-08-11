#ifndef EXPANDER_H
# define EXPENDER_H

# include "../includes/parser.h"

# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

void    expander(t_command *commands, char **envp);

#endif