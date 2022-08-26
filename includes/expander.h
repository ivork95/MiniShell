#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/parser.h"

# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

typedef struct s_expand_data
{
	size_t len;
	char *pos_dollar_sign;
	char *env_str;
	char *env_name;
	char *first_part_str;
	char *last_part_str;
	char *joined_str;
	char *new_str;
}	t_expand_data;

void	expander(t_command *commands, char **envp);
size_t	is_expandable(char *str, char *position_dollar_sign);
size_t	get_len_place_holder(char *str);
size_t	count_letters(char *str, char delimiter);
size_t	check_quote_type(char *str);
char	*get_env_value(char **envp, char *var, int var_len);
#endif