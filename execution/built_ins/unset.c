/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/21 23:00:45 by wnid-hsa         ###   ########.fr       */
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

void unset_executing(char **command, t_environ **environ, int *status)
{
    
    // printf("%s\n",command[1]);
    if(command[1])
    {
        if(ft_strcmp(command[1],"_") && !valid_unset_var_name(command[1]))
        {
            printf("bash: unset: %c%c: invalid option\n", command[1][0],command[1][1]);
            printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
            *status = 2;
            return;
        }
        if(ft_strcmp(command[1],"_") &&  unsetting_input_parsing(command[1], environ))
        {
            unsetting_input(command[1], environ);
            *status = 0;
        }
        else
        {
            *status = 0;
            return;
        }
    }
}
