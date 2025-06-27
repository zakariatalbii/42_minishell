/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:05:58 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/27 18:25:45 by wnid-hsa         ###   ########.fr       */
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
                new_value = custom_strjoin((current->next)->value, (*new)->value,1);
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
static int SHLVL_parssing(char *value)
{
    int i;

    i = 0;
    while(value[i])
    {
        if(!ft_is_a_numb(value[i]))
            return(0);
        i++;
    }
    return(1);
    
}
static void shlvl_handling(t_environ **new)
{
    if(ft_atoi((*new)->value) <= 999)
    {
        (*new)->value =ft_itoa(ft_atoi((*new)->value));
    }  
    else if(SHLVL_parssing((*new)->value) == 0)
        (*new)->value =custom_strdup("1",1);
    else if(ft_atoi((*new)->value)>999)
        (*new)->value =custom_strdup("1",1);
        
}

void handling_new_changes(t_environ **new, t_environ **environ, t_env_var **env_vars)
{ 
    if(!*new)
        return;
    if(!((*new)->value))
        return;
    else if(!ft_strcmp((*new)->operator, "+=") && !strcmp((*new)->value,""))
        return;
    if(!ft_strcmp((*new)->var,"PWD"))
        (*env_vars)->pwd =custom_strdup((*new)->value, 1);
    if(!strcmp((*new)->var, "SHLVL"))
        shlvl_handling(new);
    replace_node(new, environ); 
}

static int input_struct_handling(char *arg, int *status)
{
    int var_name_end_;
    int i;
    
        if(!arg)
            return(1);
        i = 0;
        if(!ft_strlen(arg))
        {
            perror("bash: export: not a valid identifier\n");
            *status =1;
            return(1);
        }
        while(arg[i])
        {
            var_name_end_=(var_name_end(arg));
            if(!valid_var_name(arg, var_name_end_))
            {
                if(arg[0] == '-')
                {
                    perror("bash: export: invalid option\n");
                    *status = 2;
                    return(1);
                }
                perror("bash: export: not a valid identifier\n");
                *status = 1;
                return(1);
            }
            i++;
        }
        return(0);
}

static void command_handling( int *flag, char **command, t_environ **environ , t_env_var **env_vars)
{
    t_environ *new;
    int i;
    
    i = 1 ;
    while(command && command[i])
    {
        if(valid_position_export(command[i], (*env_vars)->status))
        {
            if(input_struct_handling(command[i], (*env_vars)->status))
            {   
                *flag = 1;
                i++;
                continue;
            }
            new = ft_lstnew_environ(command[i]);
            export_flags_apdate(environ ,new,env_vars);
        }
        else
        {
                *((*env_vars)->status) = 1;
                perror("bash: export: not a valid identifier\n");
        }
            i++;
    }
}

void make_export_struct(char **command, t_environ **environ, t_env_var **env_vars)
{
    
    int flag;
     
   flag = 0;
    if(command)
    {
        command_handling(&flag, command, environ , env_vars);
        if(flag == 0)
            *((*env_vars)->status) = 0;
    }
}
