/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/22 02:08:39 by wnid-hsa         ###   ########.fr       */
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
		telda_full_path = custom_strjoin("/homes/wnid-hsa", telda_path, 1);
	}
	telda_full_path = custom_strjoin("/homes/wnid-hsa", telda_path + 1, 1);
	if(!telda_full_path)
		return(NULL);
	else
		return(telda_full_path);
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
	old_pwd = ft_getenv("OLDPWD");
	if(!chdir(old_pwd))
	{
		ft_setenv("OLDPWD", (*env_vars)->pwd,0);
		if(ft_getenv("PWD"))
			ft_setenv("PWD", old_pwd,0);
		(*env_vars)->pwd = old_pwd;
		ft_status(0);
		printf("%s\n", (*env_vars)->pwd);
	}
	else
	{
		ft_status(1);
		perror("chdir error!");
	}
}
int is_it_set(t_env **environ, char *var)
{
	t_env *current;

	current = (*environ);
	while(current)
	{
		if(!ft_strcmp(current->var,var))
		{
			if(!(current->val) || (!ft_strcmp(var,"OLDPWD") && !ft_strcmp(current->val,"")))
			{
				printf("minishell: cd: %s not set\n", var);
				return(0);
			}
			else if(!ft_strcmp(current->val, ""))
			{
				printf("minishell: cd: %s is empty\n", var);
				return(0);
			}
			return(1);
			break;
		}
		current=current->next;
	}
	printf("minishell: cd: %s not set\n", var);
	return(0);
}
