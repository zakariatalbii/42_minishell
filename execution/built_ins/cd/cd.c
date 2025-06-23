/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 10:04:10 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


static void cd_home(t_environ **environ, t_env_var **env_vars)
{
    char *HOME;
	int flag;

	flag = is_it_set(environ, "HOME");
	if(flag == 0)
	{
		*((*env_vars)->status) = 1;
		return;
	}
    HOME = getenv("HOME");
	if(!chdir(HOME))
	{
		(*env_vars)->oldpwd = custom_strdup((*env_vars)->pwd, 1);
		changing_nodes(environ, "OLDPWD",(*env_vars)->pwd);
		(*env_vars)->pwd = custom_strdup(HOME,1);
		changing_nodes(environ,"PWD", HOME);
		*((*env_vars)->status) = 0;
	}
	else
	{
		*((*env_vars)->status) = 1;
		printf("error!");
	}
}
static char *get_deleted_path_gain(char *PWD, char *new)
{
	char *deleted_path;

	char *pwd_for_path;
	pwd_for_path = custom_strjoin(PWD, "/",1);
	if(!pwd_for_path)
		return (NULL);
	deleted_path = custom_strjoin(pwd_for_path, new,1);
	if(!deleted_path)
		return(NULL);
	else
		return(deleted_path);
}
static void new_path_cd(t_environ **environ, char *new, t_env_var **env_vars)
{
    char *new_path;
	int	 flag;
	
	flag = 0;
	if(!chdir(new))
	{
		new_path = getcwd(NULL,0);
		if(!new_path)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			new_path = get_deleted_path_gain((*env_vars)->pwd, new);
			*((*env_vars)->status) = 1;
			flag = 1;
		}
		(*env_vars)->oldpwd = custom_strdup((*env_vars)->pwd, 1);
		changing_nodes(environ, "OLDPWD",(*env_vars)->pwd);
		(*env_vars)->pwd = new_path;
		changing_nodes(environ,"PWD", new_path);
		if(flag == 0)
			*((*env_vars)->status) = 0;
	}
	else
	{
		cd_errno_handling(errno, new);
		*((*env_vars)->status) = 1;
		return;
	}
}

void cd_execution(char **command , t_environ **environ, t_env_var **env_vars)
{
	char *telda_path;
	
    if(command && command[1] && command[2])
    {
        printf("bash: cd: too many arguments\n");
		*((*env_vars)->status) = 1;
        return;
    }
	else if((command)[1] && !strcmp((command)[1],"-"))
        cd_oldpwd(environ ,env_vars);
	else if ((command)[1] == NULL || ((command)[1] && !ft_strcmp(command[1], "/home/wnid-hsa")))
    	cd_home(environ, env_vars);
	else if (command[1][0] == '~' )
	{
		telda_path = telda_full_path(command[1]);
		if(!telda_path)
			return;
		new_path_cd(environ,telda_path,env_vars);
	}
	else
        new_path_cd(environ,(command)[1],env_vars);
}
