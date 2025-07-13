/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/13 18:50:03 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static int valid_unset_var_name(char *str)
// {
//     // int i;
    
//     if(!str)
//     {
//         return(-1);
//     }
//     // if(ft_is_a_numb(str[0]))
//     //     return(0);
//     // i = 0;
//     // while(str[i])
//     // {
//     //     if((!ft_is_a_numb(str[i]) && !ft_isalpha(str[i])) && str[i] != '_')
//     //     {
//     //         return(0);
//     //     }
        
//     //     i++;
//     // }
//     if(str[0] == '-')
//         return(0);
//     return(1);
    
// }
// void unsetting_input(char *variable, t_env **environ)
// {
    
//     t_env *tmp;
//     t_env *current;
    
//     tmp = (*environ);
//     while(tmp)
//     {
//         if((tmp->next) && !strcmp((tmp->next)->var, variable))
//         {
//             current = tmp;
//             tmp = (tmp->next)->next;
//             current->next = tmp;
//             break;
//         }
//         (tmp)=(tmp)->next;     
//     }
// }
// static int unsetting_input_parsing(char *variable, t_env **environ)
// {
//     t_env *current;
    
//     current = *environ;
//     while(current)
//     {
//         if(!ft_strcmp(variable,(current)->var))
//         {
//             return(1);
//         }
//         current = current->next; 
//     }
//     return(0);
// }

// void unset_executing(char **command, t_env **environ, t_env_var **env_vars)
// {
    
//     int i;
    
//     i = 1;
    
//     while(command && command[i])
//     {
//         if(ft_strcmp(command[i],"_") && !valid_unset_var_name(command[i]))
//         {
//             printf("bash: unset: %c%c: invalid option\n", command[i][0],command[i][1]);
//             printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
//             *((*env_vars)->status) = 2;
//             return;
//         }
//         if(ft_strcmp(command[i],"_") &&  unsetting_input_parsing(command[i], environ))
//         {
//             unsetting_input(command[i], environ);
//             *((*env_vars)->status) = 0;
//         }
//         else
//         {
//             *((*env_vars)->status) = 0;
//             return;
//         }
//         i++;
//     }
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 06:24:04 by wnid-hsa         ###   ########.fr       */
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
void unsetting_input(char *variable, t_env **environ)
{
    t_env *tmp;
    // int i;

    tmp = (*environ);
    if(!ft_strcmp(variable ,"PATH"))
    {
	       (void)ft_unset_flag(1);
    }
    if(tmp && !strcmp(tmp->var, variable))
    {
        *environ=(*environ)->next;
        return;
    }
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
static int unsetting_input_parsing(char *variable, t_env **environ)
{
    t_env *current;
    
    current = *environ;
    while(current)
    {
        if(!ft_strcmp(variable,(current)->var))
        {
            (void)ft_unset_flag(2);
            return(1);
        }
        current = current->next; 
    }
    if(!ft_strcmp(variable , "PATH"))
        return(2);
    if(!ft_strcmp(variable, "OLDPWD"))
    {
        return(3);
    }
    return(0);
}

void unset_executing(char **command, t_env **environ, t_env_var **env_vars)
{
    if(command[1])
    {
        if(ft_strcmp(command[1],"_") && !valid_unset_var_name(command[1]))
        {
            printf("bash: unset: %c%c: invalid option\n", command[1][0],command[1][1]);
            printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
            *((*env_vars)->status) = 2;
            return;
        }
        if(ft_strcmp(command[1],"_") )
        {
            if(unsetting_input_parsing(command[1], environ)==1)
                unsetting_input(command[1], environ);
            else if(unsetting_input_parsing(command[1], environ) == 2)
                (void)ft_unset_flag(1);
            else if(unsetting_input_parsing(command[1], environ) == 3)
            {
                (void)ft_unset_flag(2);
                *((*env_vars)->status) = 0;
            }
        }
        else
        {
            *((*env_vars)->status) = 0;
            return;
        }
    }
}