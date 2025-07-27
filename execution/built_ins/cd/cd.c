/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/27 08:39:25 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


static void cd_home(t_env **environ, t_env_var **env_vars, int flag_)
{
    char *home;
	int flag;

	flag = is_it_set(environ, "HOME");
	if(flag == 0)
	{
		ft_status(1);
		return;
	}
    home = ft_getenv("HOME");
	if(!chdir(home))
	{
		if(flag_ == 1)
			ft_setenv("OLDPWD", NULL,0);
		else 
		{
			if(ft_getenv("PWD"))
				ft_setenv("OLDPWD",ft_getenv("PWD"),0);
			else
				ft_setenv("OLDPWD", (*env_vars)->pwd,0);	
		} 
		if(ft_getenv("PWD"))
			ft_setenv("PWD", home,0);
		(*env_vars)->pwd = custom_strdup(home,1);
		ft_status(0);
	}
	else
	{
		ft_status(1);
		perror("chdir error!");
	}
}

static char *trim_back_slach(char *new)
{
	char *trimmed;
	char *new_;
	
	trimmed = custom_strtrim(new, "/");
	new_= custom_strjoin("/", trimmed,1);
	return(new_);

}
static char *get_deleted_path_gain(char *PWD, char *new)
{
	char *deleted_path;
	char *new_;

	char *pwd_for_path;
	pwd_for_path = custom_strjoin(PWD, "/",1);
	if(!pwd_for_path)
		return (NULL);
	new_ = custom_strtrim(new, "/");
	deleted_path = custom_strjoin(pwd_for_path, new_,1);
	if(!deleted_path)
		return(NULL);
	else
		return(deleted_path);
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
	
	count = 0;
	haystack = ft_strnstr(new, "..", ft_strlen(new));
	if(!haystack)
		return(0);
	count++;
	while(haystack)
	{
		haystack = ft_strnstr(new + 2, "..", ft_strlen(new));
		if(haystack)
			count++;
		new = haystack;  
	}
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
		if(!ft_strncmp(new,".",1))
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
			else
				right_pwd=pwd;
		}
		else
		{
			if(new[0] == '/')
				right_pwd =trim_back_slach(new);
			else
			{
				tmp = trim_back_slach(new);
				if(tmp)
					right_pwd= custom_strjoin(pwd,tmp,1);
			}
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
	
	trimmed = custom_strtrim(pwd, "/..");
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
			ft_status(1);
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
		ft_setenv("OLDPWD", (*env_vars)->pwd, 0);
		if(ft_getenv("PWD"))
			ft_setenv("PWD", custom_strdup(right_pwd_,1), 0);
		(*env_vars)->pwd = right_pwd_;	
		free(pwd);
		if(flag == 0)	
			ft_status(0);
	}
	else
	{
		cd_errno_handling(errno, new);
		ft_status(1);
		return;
	}
}

void cd_execution(char **command , t_env **environ, t_env_var **env_vars)
{
	char *telda_path;
	static int flag;
	
    // if(command && command[1] && command[2])
    // {
    //     ft_putstr_fd("Minishell: cd: too many arguments\n",2);
	// 	ft_status(1);
    //     return;
    // }
	if((command)[1] && !ft_strcmp((command)[1],"-"))
	{
		if(!ft_getenv("PWD"))
			flag++;
		if(ft_getenv("PWD") && flag)
			flag = 0;
        cd_oldpwd(environ ,env_vars);
	}
	else if ((command)[1] == NULL || ((command)[1] && !ft_strcmp(command[1], "/home/wnid-hsa")))
	{
		if(!ft_getenv("PWD"))
			flag++;
		if(ft_getenv("PWD") && flag)
			flag = 0;
    	cd_home(environ, env_vars, flag);
	}
	else if (command[1][0] == '~' )
	{
		if(!ft_getenv("PWD"))
			flag++;
		if(ft_getenv("PWD") && flag)
			flag = 0;
		telda_path = telda_full_path(command[1]);
		if(!telda_path)
			return;
		new_path_cd(environ,telda_path,env_vars);
	}
	else
	{
		if(!ft_getenv("PWD"))
			flag++;
		if(ft_getenv("PWD") && flag)
			flag = 0;
        new_path_cd(environ,(command)[1],env_vars);
	}
}
