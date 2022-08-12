#ifndef EXPANDER_H
# define EXPENDER_H

# include "../includes/parser.h"

# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

typedef struct s_expand_data
{
	size_t len;
	char *position_dollar_sign;
	char *env_str;
	char *env_name;
	char *first_part_str;
	char *last_part_str;
	char *joined_str;
	char *new_str;
}	t_expand_data;

void	expander(t_command *commands, char **envp);

#endif