/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/21 23:01:35 by wnid-hsa         ###   ########.fr       */
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
void changing_nodes(t_environ **environ, char *var , char *new_value)
{
	t_environ *tmp;
	
	tmp = (*environ);

	while(tmp)
	{
		if(!strcmp(tmp->var, var))
			tmp->value = ft_strdup(new_value);
		tmp = tmp->next;
	}
}

char *telda_full_path(char *telda_path)
{
	char *telda_full_path;
	
	if(!telda_path)
	{
		telda_full_path = ft_strjoin("/home/wnid-hsa", telda_path);
	}
	telda_full_path = ft_strjoin("/home/wnid-hsa", telda_path + 1);
	if(!telda_full_path)
		return(NULL);
	else
		return(telda_full_path);
}

void  cd_oldpwd(t_environ **environ, char **PWD, char **OLDPWD, int *status)
{
	char *old_pwd;
	int flag;
	old_pwd = *PWD;
	
	flag = is_it_set(environ, "OLDPWD");
	if(flag == 0)
	{
		*status = 1;
		return;
	}
	
	if(!chdir(*OLDPWD))
	{
		changing_nodes(environ,"OLDPWD", *PWD);
		changing_nodes(environ,"PWD", *OLDPWD);
		*PWD = ft_strdup(*OLDPWD);
		*OLDPWD = ft_strdup(old_pwd);
		printf("%s\n", *PWD);
	}
	else
		printf("error!");
}
int is_it_set(t_environ **environ, char *var)
{
	t_environ *current;

	current = (*environ);
	while(current)
	{
		if(!strcmp(current->var,var))
		{
			if(!(current->value))
			{
				printf("bash: cd: %s not set\n", var);
				return(0);
			}
			if(!strcmp(current->value, ""))
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