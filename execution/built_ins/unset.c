/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/29 23:31:37 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int   ft_unset_flag(int flag)
{
	static int flag_;

	if(flag == 0)
		return(flag_);
	else
	{
		flag_ = flag;
		return(flag_);
	}
}

static int valid_unset_var_name(char *str)
{
    int i;
    
    if(!str)
    {
        return(2);
    }
    if(ft_is_a_numb(str[0]))
        return(0);
    if(str[0] == '-')
        return(-1);
    i = 0;
    while(str[i])
    {
        if((!ft_is_a_numb(str[i]) && !ft_isalpha(str[i])) && str[i] != '_')
        {
            return(0);
        }
        i++;
    }
    return(1); 
}

static int unsetting_input_parsing(char *variable, t_env **environ)
{
    t_env *current;
    
    current = *environ;
    while(current)
    {
        if(!ft_strcmp(variable,(current)->var))
        {
            if(!ft_strcmp(variable , "PATH"))
            {
                (void)ft_unset_flag(1);
                return(3);
            }
            return(1);
        }
        current = current->next; 
    }
    if(!ft_strcmp(variable , "PATH"))
    {
        (void)ft_unset_flag(1);
        return(2);
    }
    return(0);
}
int invalid_var_handling(char *command, t_env_var **env_vars)
{
    if(ft_strcmp(command,"_"))
    {
        if(!valid_unset_var_name(command))
        {
            ft_putstr_fd("bash: unset: `",2);
            ft_putstr_fd(command,2);
            ft_putstr_fd("': not a valid identifier \n",2);
            ft_status(1);
            return(0);
        }
        else if (valid_unset_var_name(command) == -1)
        {
            ft_putstr_fd("bash: unset:",2);
            ft_putchar_fd(command[0],2);
            ft_putchar_fd(command[1],2);
            ft_putstr_fd(": invalid option\n",2);
            ft_status(2);
            return(0);
        }
    }
    return(1);
}
void valid_var_handling(char *command,t_env **environ, t_env_var **env_vars)
{
    if(ft_strcmp(command,"_") )
    {
        if(unsetting_input_parsing(command, environ)==1 
            || unsetting_input_parsing(command, environ)==3)
        {
            ft_unsetenv(command);
            ft_status(0);
            return;
        }
        else 
            return;
    }
    else
        ft_status(0);
}

void unset_executing(char **command, t_env **environ, t_env_var **env_vars)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    if(!command)
        return;
    while(command[++i])
    {   
        flag = invalid_var_handling(command[i], env_vars);
        if(flag == 0)
            continue;
        valid_var_handling(command[i], environ, env_vars);
    }
}