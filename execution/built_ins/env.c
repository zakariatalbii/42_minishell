/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:48 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/21 09:13:33 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *restore_user(char *pwd)
{
	char **splited_pwd;
    char *join;
    char *tmp;

	splited_pwd = ft_split(pwd,'/');
	if(!splited_pwd)
		return;
	tmp = ft_strjoin("/", splited_pwd[0]);
    if(!tmp)
        return(NULL);
    join = ft_strjoin(tmp,"/");
    if(!join)
        return(NULL);
    tmp = ft_strjoin(join, splited_pwd[1]);
    if(!tmp)
        return(NULL);
	return(tmp);
}

char *restore_path(char *user)
{
    char    *path;

    path = ft_strjoin(user, PATH_);
    return(path);
}

t_environ *restore_environ(char *pwd, int *flag)
{
    t_environ *s_environ;
    t_environ *new;

    new = ft_lstnew_environ(pwd);
    ft_lstadd_back_environ(&s_environ, new);
    new = ft_lstnew_environ("SHLVL=1");
    ft_lstadd_back_environ(&s_environ, new);
    new = ft_lstnew_environ("_=/usr/bin/env");
    ft_lstadd_back_environ(&s_environ, new);
    (1 && (s_environ = NULL));
    if(restore_user(pwd))
    {
        if(restore_path(pwd))
        {
            new = ft_lstnew(restore_path(pwd));
            ft_lstadd_back_environ(&environ, new);
            *flag = 1;
        }
        return(NULL);  
    }
    else
        return(NULL);
    return(s_environ);
}

t_environ *making_the_environ_struct(int *flag, char *pwd)
{
    extern char **environ;
    t_environ *s_environ;
    t_environ *new;
    int     flag_;
    int i;

    (1 && (s_environ = NULL) ,(flag_ = 0), i = 0);
    if(environ)
    {
        while(environ[i])
        {
            if(!strcmp(environ[i],"PATH"))
                flag_ = 1;
            new = ft_lstnew_environ(environ[i]);
            ft_lstadd_back_environ(&s_environ, new);
            i++;
        }
        if(flag_ == 0)
           s_environ = restore_environ(pwd , flag);
        return(s_environ);
    }
    else  
        return(NULL);
}

void executing_env(t_environ **environ,int *status)
{
    t_environ *current;

    if (*environ == NULL)
        return;
    current = *environ;
    while(current)
    {
        if(current->value)
        {
            printf("%s", current->var);
            printf("=");
            printf("%s", current->value);
            printf("\n");
        }
        current= current->next;
    }
    *status = 0;
}
