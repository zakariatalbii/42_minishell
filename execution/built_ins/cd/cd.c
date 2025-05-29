/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/29 00:03:41 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void cd_home(t_environ **environ, char **PWD, char **OLDPWD)
{
    char *HOME;
	int flag;

	flag =is_home_set(environ);
	if(flag ==0)
		return;
    HOME=getenv("HOME");
	if(!chdir(HOME))
	{
		*OLDPWD = ft_strdup(*PWD);
		changing_nodes(environ, "OLDPWD",*PWD);
		*PWD = ft_strdup(HOME);
		changing_nodes(environ,"PWD", HOME);
	}
	else
		printf("error!");
}
static char *get_deleted_path_gain(char *PWD, char *new)
{
	char *deleted_path;

	char *pwd_for_path;
	pwd_for_path = ft_strjoin(PWD, "/");
	if(!pwd_for_path)
		return (NULL);
	deleted_path = ft_strjoin(pwd_for_path, new);
	if(!deleted_path)
		return(NULL);
	else
		return(deleted_path);
}
static void new_path_cd(t_environ **environ, char *new, char **PWD, char **OLDPWD)
{
    char *new_path;
	
	if(!chdir(new))
	{
		new_path = getcwd(NULL,0);
		if(!new_path)
		{
			printf("getcwd cant reach directory \n");
			new_path = get_deleted_path_gain(*PWD, new);
		}
		*OLDPWD = ft_strdup(*PWD);
		changing_nodes(environ, "OLDPWD",*PWD);
		*PWD = new_path;
		changing_nodes(environ,"PWD", new_path);
	}
	else
	{
		printf("chdir error");
		return;
	}
}

void cd_execution(char **command, char **PWD, t_environ **environ, char **OLDPWD)
{
	char *telda_path;
	
    if((command)[2])
    {
        printf("too many arguments");
        return;
    }
	else if((command)[1] && !strcmp((command)[1],"-"))
        cd_oldpwd(environ ,PWD,OLDPWD);
	else if ((command)[1]== NULL || ((command)[1] && !ft_strcmp(command[1], "/home/wnid-hsa")))
    	cd_home(environ, PWD, OLDPWD);
	else if (command[1][0] == '~' )
	{
		telda_path = telda_full_path(command[1]);
		if(!telda_path)
			return;
		new_path_cd(environ,telda_path,PWD, OLDPWD);
	}
	else
        new_path_cd(environ,(command)[1],PWD, OLDPWD);
}
