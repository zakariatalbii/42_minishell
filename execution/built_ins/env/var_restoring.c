/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_restoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:53:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 05:06:37 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char *restore_user(char *pwd)
{
	char **splited_pwd;
    char *join;
    char *tmp;

	splited_pwd = ft_split(pwd,'/');
	if(!splited_pwd)
		return(NULL);
	tmp = ft_strjoin("/", splited_pwd[0]);
    if(!tmp)
        return(NULL);
    join = ft_strjoin(tmp,"/");
    if(!join)
        return(NULL);
    tmp = ft_strjoin(join, splited_pwd[1]);
    if(!tmp)
        return(NULL);
    else
        return(tmp);
}

char *restore_path(char *user)
{
    char    *path;
    char    *tmp;
    
    tmp = ft_strjoin("PATH=",user);
    if(!tmp)
        return(NULL);
    path = ft_strjoin(tmp, PATH_);
    if(!path)
        return(NULL);
    tmp = ft_strjoin(path,user);
    if(!tmp)
        return(NULL);
    path = ft_strjoin(tmp, "/.local/bin");
    return(path);
}
void restore_variables(t_environ **s_environ, t_env_var **env_vars)
{
    t_environ *new;
    char      *user;
    char      *path;
    
    new = ft_lstnew_environ("SHLVL=1");
    ft_lstadd_back_environ(s_environ, new);
    new = ft_lstnew_environ("_=/usr/bin/env");
    ft_lstadd_back_environ(s_environ, new);
    if(restore_user((*env_vars)->pwd))
    {
        if(restore_path((*env_vars)->pwd))
        {
            user=restore_user((*env_vars)->pwd);
            path =restore_path(user);
            new = ft_lstnew_environ(path);
            (*env_vars)->PATH=new->value;
            ft_lstadd_back_environ(s_environ, new);
        }
    }
}
