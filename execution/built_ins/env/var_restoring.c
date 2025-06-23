/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_restoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:53:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 09:52:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char *restore_user(char *pwd)
{
	char **splited_pwd;
    char *join;
    char *tmp;

	splited_pwd = custom_split(pwd,'/',1);
	if(!splited_pwd)
		return(NULL);
	tmp = custom_strjoin("/", splited_pwd[0],1);
    if(!tmp)
        return(NULL);
    join = custom_strjoin(tmp,"/", 1);
    if(!join)
        return(NULL);
    tmp = custom_strjoin(join, splited_pwd[1],1);
    if(!tmp)
        return(NULL);
    else
        return(tmp);
}

char *restore_path(char *user)
{
    char    *path;
    char    *tmp;
    
    tmp = custom_strjoin("PATH=",user,1);
    if(!tmp)
        return(NULL);
    path = custom_strjoin(tmp, PATH_,1);
    if(!path)
        return(NULL);
    tmp = custom_strjoin(path,user,1);
    if(!tmp)
        return(NULL);
    path = custom_strjoin(tmp, "/.local/bin",1);
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
