/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:49:08 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 03:51:22 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int env_when_restoring(t_environ *current)
{
    if(!strcmp(current->var, "PWD"))
        return(1);
    if(!strcmp(current->var, "SHLVL"))
       return(1);
    if(!strcmp(current->var, "_"))
        return(1);
    return(0);
}

void   restore_environ(t_environ **s_environ, t_env_var **env_vars)
{
    t_environ *new;
    char      *tmp;

    tmp = ft_strjoin("PWD=",(*env_vars)->pwd);
    if(tmp)
    {
        new = ft_lstnew_environ(tmp);
        ft_lstadd_back_environ(s_environ, new);
    }
    restore_variables(s_environ, env_vars);
}
static void   printing_env(t_environ *current)
{
    printf("%s", current->var);
    printf("=");
    printf("%s", current->value);
    printf("\n");  
} 

t_environ *making_the_environ_struct(int *flag, t_env_var **env_vars)
{
    extern char **environ;
    t_environ *s_environ;
    t_environ *new;
    int i;

    (1 && (s_environ = NULL) , i = 0);
    if(environ)
    {
        while(environ[i])
        {
            if(!strcmp(environ[i],restore_path(restore_user((*env_vars)->pwd))))
                *flag = 1;
            new = ft_lstnew_environ(environ[i]);
            ft_lstadd_back_environ(&s_environ, new);
            i++;
        }
        if(*flag == 0)
        {
            *((*env_vars)->env_flag) = 1;
            s_environ = NULL;
           new = ft_lstnew_environ("OLDPWD=");
            ft_lstadd_back_environ(&s_environ, new);
           restore_environ(&s_environ, env_vars);
        }
    } 
    return(s_environ);
}

void executing_env(t_environ **environ, t_env_var **env_vars)
{
    t_environ *current;

    if (*environ == NULL)
        return;
    current = *environ;
    while(current)
    {
        if(current->value)
        {
            if(*(*env_vars)->env_flag)
            {
                if(env_when_restoring(current))
                    printing_env(current);
            }      
            else
            {
                if(!strcmp(current->var, "PATH"))
                {
                    if(*((*env_vars)->export_PATH) == 1)
                        printing_env(current);
                }
                else if(!strcmp(current->var, "OLDPWD"))
                {
                    if(*((*env_vars)->export_OLDPWD) == 1)
                        printing_env(current);
                }
                else
                     printing_env(current);
            }
        }
        current= current->next;
    }
    *((*env_vars)->status) = 0;
}
