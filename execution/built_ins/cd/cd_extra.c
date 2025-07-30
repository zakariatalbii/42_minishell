/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 00:54:52 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void cd_errno_handling(int ernum, char *path)
{
	if(ernum == ENOTDIR)
	{
		ft_putstr_fd("minishell: cd: ",2);
		ft_putstr_fd(path,2);
		ft_putstr_fd(": Not a directory\n",2);
	}
	else if(ernum == EACCES)
	{
		ft_putstr_fd("cd: permission denied: ",2);
		ft_putstr_fd(path,2);
	}	
	else if(ernum == ENOENT)
	{
		ft_putstr_fd("minishell: cd: ",2);
		ft_putstr_fd(path,2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
void changing_nodes(t_env **environ, char *var , char *new_value)
{
	t_env *tmp;
	
	tmp = (*environ);
	
	while(tmp)
	{
		if(tmp->var && !ft_strcmp(tmp->var, var))
		{
			tmp->val = custom_strdup(new_value,1);	
		}
		tmp = tmp->next;
	}
}

char *telda_full_path(char *telda_path)
{
	char *telda_full_path;
	
	if(!telda_path)
	{
		telda_full_path = custom_strjoin("/mnt/homes/wnid-hsa", telda_path, 1);
	}
	telda_full_path = custom_strjoin("/mnt/homes/wnid-hsa", telda_path + 1, 1);
	if(!telda_full_path)
		return(NULL);
	else
		return(telda_full_path);
}

static void cd_oldpwd_execution(char *old_pwd, 
		t_env **environ, t_env_var **env_vars)
{
	if(!chdir(old_pwd))
	{
		ft_setenv("OLDPWD", (*env_vars)->pwd,0);
		if(ft_getenv("PWD"))
			ft_setenv("PWD", old_pwd,0);
		(*env_vars)->pwd = old_pwd;
		ft_status(0);
	}
	else
	{
		cd_errno_handling(errno, old_pwd);
		ft_status(1);
	}
}
void  cd_oldpwd(t_env **environ, t_env_var **env_vars)
{
	char *old_pwd;
	int flag;

	flag = is_it_set(environ, "OLDPWD");
	if(flag == 0)
	{
		ft_status(1);
		return;
	}
	if(ft_getenv("OLDPWD"))
	{
		old_pwd = custom_strdup(ft_getenv("OLDPWD"),1);
		printf("%s\n",old_pwd);
	}
	else
		old_pwd = (*env_vars)->pwd;
	cd_oldpwd_execution(old_pwd, environ, env_vars);

}
void print_msg(char *text1, char *text2, char *text3)
{
	ft_putstr_fd(text1,2);
	ft_putstr_fd(text2,2);
	ft_putstr_fd (text3,2);
}
int is_it_set(t_env **environ, char *var)
{
	t_env *current;

	current = (*environ);
	while(current)
	{
		if(!ft_strcmp(current->var,var))
		{
			if(!(current->val) ||
				 (!ft_strcmp(var,"OLDPWD") && !ft_strcmp(current->val,"")))
			{
				print_msg("minishell: cd: ", var, " not set\n");
				return(0);
			}
			else if(!ft_strcmp(current->val, ""))
			{
				print_msg("minishell: cd: ", var, " is empty\n");
				return(0);
			}
			return(1);
			break;
		}
		current=current->next;
	}
	print_msg("minishell: cd: ", var, " not set\n");
	return(0);
}
