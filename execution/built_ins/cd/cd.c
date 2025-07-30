/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/29 22:19:30 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int cd_flag(int flag_)
{
	static int flag;
	
	if(flag_)
	{
		if(!ft_getenv("PWD"))
			flag++;
		if(ft_getenv("PWD") && flag)
			flag = 0;
		return(flag);
	}
	else
		return(flag);
}	
static void pwdinf_update(t_env_var **env_vars, char *path)
{
	if(cd_flag(0) == 1)
	{
		ft_unsetenv("OLDPWD");
		ft_setenv("OLDPWD", NULL,0);
	}
	else 
	{
		if(ft_getenv("PWD"))
			ft_setenv("OLDPWD",ft_getenv("PWD"),0);
		else
			ft_setenv("OLDPWD", (*env_vars)->pwd,0);	
	} 
	if(ft_getenv("PWD"))
		ft_setenv("PWD", path,0);
	(*env_vars)->pwd = custom_strdup(path,1);
}
static void home_execution(t_env **environ, t_env_var **env_vars)
{
	char *home;
	
	home = ft_getenv("HOME");
	if(!chdir(home))
	{
		pwdinf_update(env_vars, home);
		ft_status(0);
	}
	else
	{
		cd_errno_handling(errno, home);
		ft_status(1);
	}
}
static void cd_home(t_env **environ, t_env_var **env_vars)
{
	int flag;

	flag = is_it_set(environ, "HOME");
	if(flag == 0)
	{
		ft_status(1);
		return;
	}
	home_execution(environ, env_vars);
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
static void cd_points_handling(char **right_pwd,char *new, char *pwd)
{
	int count;
	
	if(!ft_strncmp(new,".",1))
	{
		count = count_two_points(new);
		if(count >= 1)
		{
			while(count)
			{
				*right_pwd = go_backwards(pwd);
				pwd = *right_pwd;
				count --;
			}
		}
		else
			*right_pwd=pwd;
		}
}
char *right_pwd(t_env **environ, char *new, t_env_var **env_vars)
{
	char *right_pwd;
	char *pwd;
	char *tmp;
	int count;
	
	(1 && (pwd = (*env_vars)->pwd),(right_pwd = NULL));
	if(pwd && new)
	{
		if(!ft_strncmp(new,".",1))
			cd_points_handling(&right_pwd,new, pwd);		
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
static void cd_deleted_path(char **right_pwd_ ,char *new,
										 t_env_var **env_vars, int *flag)
{
	char *new_path;
	
	ft_putstr_fd("cd: error retrieving current directory:",2);
	ft_putstr_fd("getcwd: cannot access parent directories",2);
	ft_putstr_fd(": No such file or directory\n",2);
	new_path = get_deleted_path_gain((*env_vars)->pwd, new);
	*right_pwd_ = new_path;
	ft_status(1);
	(*flag)++;
}
static void cd_new_core(t_env **environ,char *new, int *flag,
													 t_env_var **env_vars)
{
	char *pwd;
	char *prev_pwd;
	char *right_pwd_;
	
	(1 && (pwd = getcwd(NULL,0)),
						(prev_pwd=(*env_vars)->pwd),(right_pwd_ = NULL));
	if(!pwd)
		cd_deleted_path(&right_pwd_ ,new, env_vars, flag);
	else
	{
		if(*flag >0)
		{
			right_pwd_=escaped_path(prev_pwd, *flag);
			*flag = 0;
		}
		else
			right_pwd_=right_pwd(environ, new, env_vars);
	}
	pwdinf_update(env_vars, right_pwd_);
	free(pwd);
	if(*flag == 0)	
		ft_status(0);
}
static void new_path_cd(t_env **environ, char *new, t_env_var **env_vars)
{
	static int	 flag;
	char *right_pwd_;

	if(!chdir(new))
		cd_new_core(environ,new, &flag, env_vars);
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
	
	(void)cd_flag(1);
	if((command)[1] && !ft_strcmp((command)[1],"-"))
        cd_oldpwd(environ ,env_vars);
	else if ((command)[1] == NULL || ((command)[1] && 
		!ft_strcmp(command[1], "/home/wnid-hsa")))
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
