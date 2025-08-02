/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:10 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	home_execution(t_env_var **env_vars)
{
	char	*home;

	home = ft_getenv("HOME");
	if (!chdir(home))
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

static void	cd_home(t_env **environ, t_env_var **env_vars)
{
	int	flag;

	flag = is_it_set(environ, "HOME");
	if (flag == 0)
	{
		ft_status(1);
		return ;
	}
	home_execution(env_vars);
}

static void	cd_new_core(char *new, int *flag, t_env_var **env_vars)
{
	char	*pwd;
	char	*prev_pwd;
	char	*right_pwd_;

	(1 && (pwd = getcwd(NULL, 0)),
		(prev_pwd = (*env_vars)->pwd), (right_pwd_ = NULL));
	if (!pwd)
		cd_deleted_path(&right_pwd_, new, env_vars, flag);
	else
	{
		if (*flag > 0)
		{
			right_pwd_ = escaped_path(prev_pwd, *flag);
			*flag = 0;
		}
		else
			right_pwd_ = right_pwd(new, env_vars);
	}
	pwdinf_update(env_vars, right_pwd_);
	free (pwd);
	if (*flag == 0)
		ft_status(0);
}

static void	new_path_cd(char *new, t_env_var **env_vars)
{
	static int	flag;

	if (!chdir(new))
		cd_new_core(new, &flag, env_vars);
	else
	{
		cd_errno_handling(errno, new);
		ft_status(1);
		return ;
	}
}

void	cd_execution(char **command, t_env **environ, t_env_var **env_vars)
{
	char		*telda_path;

	(void)cd_flag(1);
	if ((command)[1] == NULL || ((command)[1] &&
		!ft_strcmp(command[1], (*env_vars)->home)))
		cd_home(environ, env_vars);
	else if (command[1][0] == '~' )
	{
		telda_path = telda_full_path(command[1],env_vars);
		if (!telda_path)
			return ;
		new_path_cd(telda_path, env_vars);
	}
	else
		new_path_cd((command)[1], env_vars);
}
