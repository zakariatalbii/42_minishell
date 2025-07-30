/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:56 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/29 23:22:54 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
   return(0);
}

static void export_no_arg(t_env **environ, t_env_var **env_vars)
{
    t_env *current;

    current = (*environ);
    while(current)
    {
        export_printing_conditions(current, env_vars);
        current = current->next;
    }
}

void export_execution(char **command, t_env **environ, t_env_var **env_vars)
{
    if(command)
    {
        if(!command[1])
        {
            export_no_arg(environ,env_vars);
            ft_status(0);
            return;
        }
        make_export_struct(command,environ,env_vars);
        // ft_status(0);
    }
}
