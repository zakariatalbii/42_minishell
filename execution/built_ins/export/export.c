/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:56 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/30 01:11:24 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

static void export_no_arg(t_environ **environ)
{
    t_environ *current;

    current = (*environ);
    while(current)
    {
        printf("declare -x ");
        printf("%s", current->var);
        if(current->value)
        {
            printf("=");
            printf("\"%s\"", current->value);
        }
        printf("\n");
        current = current->next;
    }
}
void export_execution(char **command, t_environ **environ, char **PWD)
{
    int i;

    if(command)
    {
        i = 1;
        if(!command[1])
        {
            export_no_arg(environ);
            return;
        }
        make_export_struct(command,environ, PWD);
        
    }
}

