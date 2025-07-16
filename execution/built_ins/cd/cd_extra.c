/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/16 00:39:41 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void cd_errno_handling(int ernum, char *path)
{
	if(ernum == ENOTDIR)
		printf("bash: cd: %s: Not a directory\n", path);
	else if(ernum == EACCES)
		printf("cd: permission denied: %s", path);
	else if(ernum == ENOENT)
		printf("bash: cd: %s: No such file or directory\n", path);
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
	old_pwd = get_value("OLDPWD", *environ);

	flag = is_it_set(environ, "OLDPWD");
	if(flag == 0)
	{
		*((*env_vars)->status) = 1;
		return;
	}
	if(!chdir(get_value("OLDPWD", *environ)))
	{
		save_node_changes(environ,"OLDPWD", (get_value("PWD",*environ)));
		// save_node_changes(environ,"PWD", old_pwd);
		changing_nodes(environ,"PWD", old_pwd);
		if((*env_vars)->pwd)
			(*env_vars)->pwd = custom_strdup(old_pwd,1);
		if(get_value("PWD",*environ))
			printf("%s\n", get_value("PWD",*environ));
		else
			printf("%s\n", (*env_vars)->pwd);
	}
	else
		printf("error!");
}
int is_it_set(t_env **environ, char *var)
{
	t_env *current;

	current = (*environ);
	while(current)
	{
		if(!strcmp(current->var,var))
		{
			if(!(current->val))
			{
				printf("bash: cd: %s not set\n", var);
				return(0);
			}
			if(!strcmp(current->val, ""))
			{
				printf("bash: cd: %s is empty\n", var);
				return(0);
			}
			return(1);
			break;
		}
		current=current->next;
	}
	printf("bash: cd: %s not set\n", var);
	return(0);
}
