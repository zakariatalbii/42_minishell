/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:56 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/24 10:26:27 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int export_when_restoring(t_environ *current)
{
    if(!strcmp(current->var, "OLDPWD"))
        return(1);
    if(!strcmp(current->var, "PWD"))
        return(1);
    if(!strcmp(current->var, "SHLVL"))
       return(1);
    return(0);
}
void   printing_export(t_environ *current)
{
    printf("declare -x ");
    printf("%s", current->var);
    if(current->value)
    {
        printf("=");
        printf("\"%s\"", current->value);
    }
    printf("\n");
}

int is_the_var_in_environ(char *variable, t_environ *environ)
{
    t_environ *current = environ;
    if(!variable)
        return(-1);
   while(current)
   {
       if(!strcmp(current->var ,variable))
       {
           return(1);
       }
       current = current->next;
   }
   return(0);
}

static void export_no_arg(t_environ **environ, t_env_var **env_vars)
{
    t_environ *current;

    current = (*environ);
    while(current)
    {
        if(*(*env_vars)->env_flag)
        {
            if(export_when_restoring(current))
               printing_export(current); 
        }
        else
        {
            export_printing_conditions(current, env_vars);
            // if(!strcmp(current->var, "PATH"))
            // {
            //     if(*((*env_vars)->export_PATH) == 1)
            //         printing_export(current);
            // }
            // else if(!strcmp(current->var, "_"))
            // {
            //     if(*((*env_vars)->export_) == 1)
            //         printing_export(current);
            // }       
            // else
            //     printing_export(current);
        }
        current = current->next;
    }
}

void export_execution(char **command, t_environ **environ, t_env_var **env_vars)
{
    if(command)
    {
        if(!command[1])
        {
            export_no_arg(environ, env_vars);
            *((*env_vars)->status) = 0;
            return;
        }
        make_export_struct(command,environ,env_vars);
        *((*env_vars)->env_flag) = 0;
    }
}

