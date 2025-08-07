/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/07 17:13:57 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*telda_full_path(char *telda_path)
{
	char	*telda_full_path;
	char	*home;

	home = custom_strdup("/mnt/homes/wnid-hsa", 1);
	if (!telda_path)
	{
		telda_full_path = custom_strjoin(home, telda_path, 1);
	}
	telda_full_path = custom_strjoin(home, telda_path + 1, 1);
	if (!telda_full_path)
		return (NULL);
	else
		return (telda_full_path);
}

static void	cd_oldpwd_execution(char *old_pwd,
	t_env_var **env_vars, t_env **environ)
{
	if (!chdir(old_pwd))
	{
		pwdinf_update(env_vars, old_pwd, environ);
		(*env_vars)->pwd = old_pwd;
		ft_status(0);
	}
	else
	{
		cd_errno_handling(errno, old_pwd);
		ft_status(1);
	}
}

int	cd_old_flag(int flag_, char *path, t_env *environ)
{
	static int	flag;

	if (flag_ && path)
	{
		if (!is_the_var_in_environ("OLDPWD", environ) && !ft_strcmp(path, "-"))
			flag++;
		else
			flag = 0;
		return (flag);
	}
	else
		return (flag);
}

void	cd_oldpwd(t_env **environ, t_env_var **env_vars)
{
	char	*old_pwd;
	int		flag;

	flag = is_it_set(environ, "OLDPWD");
	if (flag == 0)
	{
		ft_status(1);
		return ;
	}
	old_pwd = custom_strdup(ft_getenv("OLDPWD"), 1);
	printf("%s\n", old_pwd);
	(*env_vars)->oldpwd = old_pwd;
	cd_oldpwd_execution(old_pwd, env_vars, environ);
}
