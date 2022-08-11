/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 02:05:30 by ivork         #+#    #+#                 */
/*   Updated: 2022/08/10 20:10:28 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/expander.h"
#include <stdlib.h>
#include "../libft/libft.h"

size_t check_quote_type(char *str)
{
    if (*str == '\'')
        return (SINGLE_QUOTES);
    else if (*str == '\"')
        return (DOUBLE_QUOTES);
    else
        return (0);
}

char *get_envp_variable(char* str, char **envp)
{
    while(*envp)
    {
        if ()
    }
}

char *handle_single_quotes(char *str)
{
    size_t len;
    char * new_str;
    
    len = ft_strlen(str);
    new_str = malloc(sizeof(char) * len - 1);
    ft_strlcpy(new_str, str + 1, len -1);
    free(str);
    return (new_str);
    
}

void    expand_command(t_command *command, char **envp)
{
    size_t i;
    size_t quote_type;

        quote_type = check_quote_type(command->cmd);
        if (quote_type == SINGLE_QUOTES)
        {
            command->cmd = handle_single_quotes(command->cmd);
            command->args[0] = command->cmd;
        }
        else if (quote_type == DOUBLE_QUOTES)
        {
            if (ft_strchr(command->cmd, '$'))
            {
                command->cmd =  get_envp_variable()
            }
        }

}

void    expand_args(t_command *command, char **envp)
{
    size_t i;
    size_t quote_type;

    i = 0;
    while(command->args[i])
    {
        quote_type = check_quote_type(command->args[i]);
        if (quote_type == SINGLE_QUOTES)
        {
            command->args[i] = handle_single_quotes(command->args[i]);
        }
        // else if (quote_type == DOUBLE_QUOTES)
        
        i++;
    }
}

void    expander(t_command *commands, char **envp)
{
    // t_command *tmp;

    // tmp = commands;
    expand_command(commands, envp);
    expand_args(commands, envp);
    // while (tmp)
    // {
    //     expand_args(commands, envp);
    //     tmp = tmp->next;
    // }
    // return (commands);
}