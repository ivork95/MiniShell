#ifndef MINICORE_H
# define MINICORE_H

#include "../../includes/structs.h"
#include "../../includes/builtins.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include "../../includes/executor.h"

char	*two_d_to_str(char **environ);
void minicore(char **test_inputs, t_env_var **onze_env);

#endif
