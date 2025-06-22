/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:49:08 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/22 00:56:45 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// char *restore_user(char *pwd)
// {
// 	char **splited_pwd;
//     char *join;
//     char *tmp;

// 	splited_pwd = ft_split(pwd,'/');
// 	if(!splited_pwd)
// 		return(NULL);
// 	tmp = ft_strjoin("/", splited_pwd[0]);
//     if(!tmp)
//         return(NULL);
//     join = ft_strjoin(tmp,"/");
//     if(!join)
//         return(NULL);
//     tmp = ft_strjoin(join, splited_pwd[1]);
//     if(!tmp)
//         return(NULL);
//     else
//         return(tmp);
// }

// char *restore_path(char *user)
// {
//     char    *path;
//     char    *tmp;
    
//     tmp = ft_strjoin("PATH=",user);
//     if(!tmp)
//         return(NULL);
//     path = ft_strjoin(tmp, PATH_);
//     if(!path)
//         return(NULL);
//     tmp = ft_strjoin(path,user);
//     if(!tmp)
//         return(NULL);
//     path = ft_strjoin(tmp, "/.local/bin");
//     return(path);
// }
// void restore_variables(t_environ **s_environ, char *pwd)
// {
//     t_environ *new;
//     char      *user;
//     char      *path;
    
//     new = ft_lstnew_environ("SHLVL=1");
//     ft_lstadd_back_environ(s_environ, new);
//     new = ft_lstnew_environ("_=/usr/bin/env");
//     ft_lstadd_back_environ(s_environ, new);
//     if(restore_user(pwd))
//     {
//         if(restore_path(pwd))
//         {
//             user=restore_user(pwd);
//             path =restore_path(user);
//             new = ft_lstnew_environ(restore_path(pwd));
//             ft_lstadd_back_environ(s_environ, new);
//         }
//     }
// }

void   restore_environ(t_environ **s_environ, char *pwd, int flag)
{
    t_environ *new;
    char      *tmp;

    (void)flag;
    tmp = ft_strjoin("PWD=",pwd);
    if(tmp)
    {
        new = ft_lstnew_environ(tmp);
        ft_lstadd_back_environ(s_environ, new);
    }
    restore_variables(s_environ, pwd);
}

t_environ *making_the_environ_struct(int *flag, char *pwd)
{
    extern char **environ;
    t_environ *s_environ;
    t_environ *new;
    int i;

    (1 && (s_environ = NULL) , i = 0);
    if(environ)
    {
        while(environ[i])
        {
            if(!strcmp(environ[i],restore_path(restore_user(pwd))))
                *flag = 1;
            new = ft_lstnew_environ(environ[i]);
            ft_lstadd_back_environ(&s_environ, new);
            i++;
        }
        if(*flag == 0)
        {
            s_environ = NULL;
           new = ft_lstnew_environ("OLDPWD=");
            ft_lstadd_back_environ(&s_environ, new);
           restore_environ(&s_environ, pwd,*flag);
        }
    } 
    return(s_environ);
}

void executing_env(t_environ **environ, int *status)
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
