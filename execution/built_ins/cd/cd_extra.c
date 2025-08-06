/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/04 04:11:51 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*telda_full_path(char *telda_path, t_env_var **env_vars)
{
	char	*telda_full_path;

	if (!telda_path)
	{
		telda_full_path = custom_strjoin((*env_vars)->home, telda_path, 1);
	}
	telda_full_path = custom_strjoin((*env_vars)->home, telda_path + 1, 1);
	if (!telda_full_path)
		return (NULL);
	else
		return (telda_full_path);
}

// static void	cd_oldpwd_execution(char *old_pwd, t_env_var **env_vars)
// {
// 	if (!chdir(old_pwd))
// 	{
// 		if(ft_getenv("OLDPWD"))
// 			ft_setenv("OLDPWD", (*env_vars)->pwd, 0);
// 		if (ft_getenv("PWD"))
// 			ft_setenv("PWD", old_pwd, 0);
// 		(*env_vars)->pwd = old_pwd;
// 		ft_status(0);
// 	}
// 	else
// 	{
// 		cd_errno_handling(errno, old_pwd);
// 		ft_status(1);
// 	}
// }
// int	cd_old_flag(int flag_, char *path, t_env *environ)
// {
// 	static int	flag;

// 	if (flag_ && path)
// 	{
// 		if (!is_the_var_in_environ("OLDPWD", environ) && !ft_strcmp(path,"-"))
// 			flag++;
// 		else
// 			flag = 0;
// 		return (flag);
// 	}
// 	else
// 		return (flag);
// }

// void	cd_oldpwd(t_env **environ, t_env_var **env_vars, char **command)
// {
// 	char	*old_pwd;
// 	int		flag;

// 	if(cd_old_flag(0, NULL, environ) > 0)
// 	{
// 		(void)is_it_set(environ, "OLDPWD");
// 		ft_status(1);
// 		return ;
// 	}
// 	if (ft_getenv("OLDPWD"))
// 	{
// 		old_pwd = custom_strdup(ft_getenv("OLDPWD"), 1);
// 		printf("%s\n", old_pwd);
// 	}
// 	else
// 		old_pwd = (*env_vars)->pwd;
// 	(*env_vars)->oldpwd = old_pwd;
// 	cd_oldpwd_execution(old_pwd, env_vars);
// }
