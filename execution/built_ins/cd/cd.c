/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/16 05:33:18 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


static void cd_home(t_env **environ, t_env_var **env_vars)
{
    char *HOME;
	int flag;
	char *pwd;

	flag = is_it_set(environ, "HOME");
	if(flag == 0)
	{
		*((*env_vars)->status) = 1;
		return;
	}
    HOME = get_value("HOME",*environ);
	pwd = get_value("PWD",*environ);
	if(!pwd)
		save_node_changes(environ, "OLDPWD", (*env_vars)->pwd);
	else
		save_node_changes(environ, "OLDPWD", pwd);
	if(!chdir(HOME))
	{
		changing_nodes(environ,"PWD", HOME);
		(*env_vars)->pwd = custom_strdup(HOME,1);
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
void save_node_changes(t_env **environ, char *var, char *new_value)
{
	t_env *new_node;

	new_node = ft_envnew(var,new_value);
	if(!new_node)
		return;
	if(!ft_strcmp(var, "OLDPWD"))
	{
		if(!new_node->val)
		{
			(new_node)->val = custom_strdup("",1);
		}
	}
	if(!is_the_var_in_environ(var,*environ) && !ft_unset_flag(0))
	{	
		ft_envadd(environ, new_node);
	}
	else
	{
		changing_nodes(environ, var,new_value);
	
	}
}
char *go_backwards(char *pwd)
{
	int i;
	int lengh;
	char *path;
	int count;
	
	if(!pwd)
		return(NULL);
	(1 && (lengh = count_words(pwd, '/')),(count = 0), (i = -1));
	if(!ft_strcmp(pwd,"/"))
		path = custom_strdup(pwd,1);
	else
	{
		while(pwd[++i] && count <lengh)
		{
			if(pwd[i]=='/')
			{
				count++;
			}
		}
		if(i == 1)
			path = custom_strndup(pwd ,i ,1);
		else
			path = custom_strndup(pwd ,i - 1,1);
	}
	return(path);
}
static int count_two_points(char *new)
{
	int count;
	char *haystack;

	count = 1;
	haystack = ft_strnstr(new, "..", ft_strlen(new));
	if(!haystack)
		return(0);
	while(haystack)
	{
		haystack = ft_strnstr(new + 2, "..", ft_strlen(new));
		count++;
		new = haystack;  
	}
	if(count > 1)
		return(count -1);
	return(count);
} 

char *right_pwd(t_env **environ, char *new, t_env_var **env_vars)
{
	char *right_pwd;
	char *pwd;
	char *tmp;
	int count;
	
	(1 && (pwd = (*env_vars)->pwd),(right_pwd = NULL));
	if(!pwd)
		return(NULL);
	if(new)
	{
		if(!ft_strcmp(new,"."))
			right_pwd =custom_strdup(pwd ,1);
		else if(new[0] =='/')
			right_pwd =custom_strdup(new ,1);
		else if(!ft_strncmp(new,"..",2))
		{
			count = count_two_points(new);
			if(count >= 1)
			{
				while(count)
				{
					right_pwd = go_backwards(pwd);
					pwd = right_pwd;
					count --;
				}
			} 
		}
		else
		{
			tmp = custom_strjoin(pwd,"/",1);
			right_pwd= custom_strjoin(tmp,new,1);
		}	
		return(right_pwd);
	}
	return(NULL);
}

static char *escaped_path(char *pwd, int flag)
{
	char *trimmed;
	int count;
	int lengh;
	
	count = (flag + 1 )*2;
	
	trimmed = ft_strtrim(pwd, "/..");
	if(!trimmed)
		return(NULL);
	lengh = ft_strlen(trimmed) - count;
	return(custom_strndup(trimmed, lengh,1));
}
static void new_path_cd(t_env **environ, char *new, t_env_var **env_vars)
{
    char *new_path;
	static int	 flag;
	char *right_pwd_;
	char *previous_pwd;
	char *pwd;

	right_pwd_ = NULL;
	if(!chdir(new))
	{
		pwd = getcwd(NULL,0);
		previous_pwd=(*env_vars)->pwd;
		if(!pwd)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			new_path = get_deleted_path_gain((*env_vars)->pwd, new);
			right_pwd_ = new_path;
			*((*env_vars)->status) = 1;
			flag++;
		}
		else
		{
			if(flag >0)
			{
				right_pwd_=escaped_path(previous_pwd, flag);
				flag = 0;
				
			}
			else
				right_pwd_=right_pwd(environ, new, env_vars);
		}
		save_node_changes(environ, "OLDPWD", (*env_vars)->pwd);
		changing_nodes(environ, "PWD",custom_strdup(right_pwd_,1));
		(*env_vars)->pwd = right_pwd_;	
		free(pwd);
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

void cd_execution(char **command , t_env **environ, t_env_var **env_vars)
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
