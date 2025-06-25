/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/25 17:58:10 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int valid_unset_var_name(char *str)
{
    // int i;
    
    if(!str)
    {
        return(-1);
    }
    // if(ft_is_a_numb(str[0]))
    //     return(0);
    // i = 0;
    // while(str[i])
    // {
    //     if((!ft_is_a_numb(str[i]) && !ft_isalpha(str[i])) && str[i] != '_')
    //     {
    //         return(0);
    //     }
        
    //     i++;
    // }
    if(str[0] == '-')
        return(0);
    return(1);
    
}
void unsetting_input(char *variable, t_environ **environ)
{
    
    t_environ *tmp;
    
    tmp = (*environ);
    while(tmp)
    {
        if((tmp->next) && !strcmp((tmp->next)->var, variable))
        {
            tmp->next = (tmp->next)->next;
            break;
        }
        tmp=tmp->next;     
    }
}
static int unsetting_input_parsing(char *variable, t_environ **environ)
{
    t_environ *current;
    
    current = *environ;
    while(current)
    {
        if(!ft_strcmp(variable,(current)->var))
        {
            return(1);
        }
        current = current->next; 
    }
    return(0);
}

void unset_executing(char **command, t_environ **environ, t_env_var **env_vars)
{
    
    int i;
    
    i = 1;
    
    while(command && command[i])
    {
        if(ft_strcmp(command[i],"_") && !valid_unset_var_name(command[i]))
        {
            printf("bash: unset: %c%c: invalid option\n", command[i][0],command[i][1]);
            printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
            *((*env_vars)->status) = 2;
            return;
        }
        if(ft_strcmp(command[i],"_") &&  unsetting_input_parsing(command[i], environ))
        {
            unsetting_input(command[i], environ);
            *((*env_vars)->status) = 0;
        }
        else
        {
            *((*env_vars)->status) = 0;
            return;
        }
        i++;
    }
}
