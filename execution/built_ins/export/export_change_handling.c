/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:05:58 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/29 05:06:49 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../minishell.h"


static void replace_node(t_environ **new, t_environ **environ)
{
    t_environ *tmp;
    t_environ *current;
    
    char *new_value;
    tmp = (*environ);
    while(tmp)
    {
        if((tmp->next) && !strcmp((tmp->next)->var, (*new)->var))
        {
            current = tmp;
            tmp = (tmp->next)->next;
            if(!strcmp((*new)->operator, "+="))
            {
                new_value = ft_strjoin((current->next)->value, (*new)->value);
                if(!new_value)
                    return;
                (*new)->value = new_value;
            }
            (*new)->next = tmp;
            current->next = *new;
            break;
        }
        tmp=tmp->next;     
    }
}

static void handling_new_changes(t_environ **new, t_environ **environ)
{ 
    if(!*new)
        return;
    if(!((*new)->value))
        return;
    else if(!ft_strcmp((*new)->operator, "+=") && !strcmp((*new)->value,""))
        return;
    replace_node(new, environ); 
}

static int input_struct_handling(char *arg)
{
    int var_name_end_;
    int i;
    
        if(!arg)
            return(1);
        i = 0;
        while(arg[i])
        {
            var_name_end_=(var_name_end(arg));
            if(!valid_var_name(arg, var_name_end_))
            {
                printf("syntax error!\n");
                    return(1);
            }
            i++;
        }
        return(0);
 
}

// void make_export_struct(char **command, t_environ **environ) {
//     t_environ *new;
//     int i = 1;

//     while (command[i]) 
//     {
//         if (valid_position_export(command[i])) {
//             if (input_struct_handling(command[i])) {
//                 i++;
//                 continue;
//             }
//             new = ft_lstnew_environ(command[i]);
//             if (is_the_var_in_environ(new->var, *environ)) {
//                 handling_new_changes(&new, environ);
//             } else {
//                 ft_lstadd_back_environ(environ, new);
//             }
//         } else {
//             printf("syntax error!\n");
//         }
//         if (command[i] && command[i][0])
//             i++;
//     }
// }


void make_export_struct(char **command, t_environ **environ)
{
    t_environ *new;
    int count ;
    int i;
    
   (1 && (count = 0), (i = 1 ));
    if(command)
    {
        while(command[i])
        {
            if(valid_position_export(command[i]))
            {
                if(input_struct_handling(command[i]))
                {   
                    i++;
                    continue;
                }
                new = ft_lstnew_environ(command[i]);
                if(is_the_var_in_environ(new->var, *environ))
                    handling_new_changes(&new, environ);
                else
                    ft_lstadd_back_environ(environ, new);
            }
            else
                printf("syntax error!\n");
            i++;
        }
    }
}