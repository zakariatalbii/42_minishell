/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/21 05:58:49 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


static void cd_home(t_environ **environ, char **PWD, char **OLDPWD, int *status)
{
    char *HOME;
	int flag;

	flag = is_it_set(environ, "HOME");
	if(flag == 0)
	{
		*status = 1;
		return;
	}
    HOME = getenv("HOME");
	if(!chdir(HOME))
	{
		*OLDPWD = ft_strdup(*PWD);
		changing_nodes(environ, "OLDPWD",*PWD);
		*PWD = ft_strdup(HOME);
		changing_nodes(environ,"PWD", HOME);
		*status = 0;
	}
	else
	{
		*status = 1;
		printf("error!");
	}
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
static void new_path_cd(t_environ **environ, char *new, char **PWD, char **OLDPWD, int *status)
{
    char *new_path;
	int	 flag;
	
	if(!chdir(new))
	{
		new_path = getcwd(NULL,0);
		if(!new_path)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			new_path = get_deleted_path_gain(*PWD, new);
			*status = 1;
			flag = 1;
		}
		*OLDPWD = ft_strdup(*PWD);
		changing_nodes(environ, "OLDPWD",*PWD);
		*PWD = new_path;
		changing_nodes(environ,"PWD", new_path);
		if(flag == 0)
			*status = 0;
	}
	else
	{
		cd_errno_handling(errno, new);
		*status = 1;
		return;
	}
}

void cd_execution(char **command, char **PWD, t_environ **environ, char **OLDPWD, int *status)
{
	char *telda_path;
	
    if(command && command[1] && command[2])
    {
        printf("bash: cd: too many arguments\n");
		*status = 1;
        return;
    }
	else if((command)[1] && !strcmp((command)[1],"-"))
        cd_oldpwd(environ ,PWD,OLDPWD, status);
	else if ((command)[1] == NULL || ((command)[1] && !ft_strcmp(command[1], "/home/wnid-hsa")))
    	cd_home(environ, PWD, OLDPWD, status);
	else if (command[1][0] == '~' )
	{
		telda_path = telda_full_path(command[1]);
		if(!telda_path)
			return;
		new_path_cd(environ,telda_path,PWD, OLDPWD, status);
	}
	else
        new_path_cd(environ,(command)[1],PWD, OLDPWD, status);
}
