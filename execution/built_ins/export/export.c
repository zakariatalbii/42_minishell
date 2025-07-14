/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:56 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/13 23:49:45 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// static int export_when_restoring(t_env *current)
// {
//     if(!strcmp(current->var, "OLDPWD"))
//         return(1);
//     if(!strcmp(current->var, "PWD"))
//         return(1);
//     if(!strcmp(current->var, "SHLVL"))
//        return(1);
//     return(0);
// }
void   printing_export(t_env *current)
{
    printf("declare -x ");
    printf("%s", current->var);
    if(current->val)
    {
        printf("=");
        printf("\"%s\"", current->val);
    }
        printf("\n");
}

int is_the_var_in_environ(char *variable, t_env *environ)
{
    t_env *current = environ;
    if(!variable)
        return(-1);
   while(current)
   {
       if(current->var && !ft_strcmp(current->var ,variable))
       {
           return(1);
       }
       current = current->next;
   }
//    printf("you are fine\n");
   return(0);
}

static void export_no_arg(t_env **environ)
{
    t_env *current;

    current = (*environ);
    if(!is_the_var_in_environ("OLDPWD",*environ))
    {
        if(!ft_unset_flag(0) )
        {
            printf("declare -x ");
            printf("OLDPWD\n");
        }
    }
    while(current)
    {
        // if(*(*env_vars)->env_flag)
        // {
        //     if(export_when_restoring(current))
        //        printing_export(current); 
        // }
        // else
        // {
        //     export_printing_conditions(current, env_vars);
        //     // if(!strcmp(current->var, "PATH"))
        //     // {
        //     //     if(*((*env_vars)->export_PATH) == 1)
        //     //         printing_export(current);
        //     // }
        //     // else if(!strcmp(current->var, "_"))
        //     // {
        //     //     if(*((*env_vars)->export_) == 1)
        //     //         printing_export(current);
        //     // }       
        //     // else
        //     //     printing_export(current);
        // }
        printing_export(current);
        current = current->next;
    }
}

void export_execution(char **command, t_env **environ, t_env_var **env_vars)
{
    if(command)
    {
        if(!command[1])
        {
            export_no_arg(environ);
            *((*env_vars)->status) = 0;
            return;
        }
        make_export_struct(command,environ,env_vars);
        *((*env_vars)->env_flag) = 0;
    }
}
