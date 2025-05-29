/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/29 00:01:42 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

void  cd_oldpwd(t_environ **environ, char **PWD, char **OLDPWD)
{
	char *old_pwd;
	old_pwd = *PWD;

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
int is_home_set(t_environ **environ)
{
	t_environ *current;

	current = (*environ);
	while(current)
	{
		if(!strcmp(current->var,"HOME"))
		{
			if(!(current->value))
			{
				printf("home is unset\n");
				return(0);
			}
			if(!strcmp(current->value, ""))
			{
				printf("home is set but empty\n");
				return(0);
			}
			return(1);
			break;
		}
		current=current->next;
	}
	printf("home is unset\n");
	return(0);
}