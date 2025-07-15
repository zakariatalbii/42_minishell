/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:06 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/15 06:31:22 by wnid-hsa         ###   ########.fr       */
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
    // char *pwd_;
    
    if (command[1] && !is_valid_pwd(command))
    {
        ft_putstr_fd("Minishell: pwd: ",2);
        ft_putchar_fd(command[1][0],2);
        ft_putchar_fd(command[1][1],2);
        ft_putstr_fd(": invalid option\n",2);
        *(*env_vars)->status = 2;
        return;
    }
    else
    {   
        // *((*env_vars)->status) = 0;
        // if(get_value("PWD",environ))
        //     printf("%s\n", get_value("PWD",environ));
			printf("%s\n", (*env_vars)->pwd);
             
    }
}

