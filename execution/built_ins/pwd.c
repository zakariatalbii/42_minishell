/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:06 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/13 21:29:37 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_valid_pwd(char **command)
{
    if (!ft_strcmp(command[1],"-p") || !ft_strcmp(command[1],"--p" ) || !ft_strcmp(command[1],"---p"))
        return(0);
    else
        return(1);
}
char *get_value(char *var,t_env *environ)
{
    while(environ)
    {
        if(!strcmp(environ->var ,var))
           return(environ->val);
        environ=environ->next;
    }
    return(NULL);
}

void  pwd_execution(char **command, t_env *environ, t_env_var **env_vars)
{
    if (command[1] && !is_valid_pwd(command))
    {
        printf("bash: pwd: %s: invalid option\n", command[1]);
        *(*env_vars)->status = 2;
        return;
    }
    else
    {   
        *((*env_vars)->status) = 0;
        if(get_value("PWD",environ))
            printf("%s\n", get_value("PWD",environ));
        else
        { 
            if((*env_vars)->pwd)
			   printf("%s\n", (*env_vars)->pwd);
        }
    }
}
