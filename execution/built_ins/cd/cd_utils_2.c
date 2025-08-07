/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:39:07 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/07 15:17:57 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	cd_flag(int flag_)
{
	static int	flag;

	(void)flag_;
	if(unset_pwd_flag(0) == 1 || (ft_getenv("PWD") && flag))
	{
		flag = 0;
	}
	else 
	{
		flag++;
	}
	return (flag);
}
void	pwdinf_update(t_env_var **env_vars, char *path, t_env **environ)
{
	char	*oldpwd;
	
	oldpwd = (*env_vars)->pwd;
	if (ft_getenv("PWD"))
		oldpwd = custom_strdup(ft_getenv("PWD"), 1);
	else
		oldpwd = (*env_vars)->pwd;
	if(is_the_var_in_environ("OLDPWD",*environ))
	{
		if (!ft_getenv("PWD"))
		{
			if(cd_flag(0) == 0)
            	ft_setenv("OLDPWD", "", 0);
			else
				ft_setenv("OLDPWD", oldpwd, 0);
		}
		else
			ft_setenv("OLDPWD", oldpwd, 0);
	}
	if (ft_getenv("PWD"))
		ft_setenv("PWD", path, 0);
	(*env_vars)->oldpwd = oldpwd;
	(*env_vars)->pwd = custom_strdup(path, 1);
	(void)unset_pwd_flag(-1);
}

char	*trim_back_slach(char *new, char *pwd)
{
	char	*trimmed;
	char	*tmp;
	char	*new_;

	trimmed = custom_strtrim(new, "/");
	if(!pwd)
	{
		new_ = custom_strjoin("/", trimmed, 1);
	}
	else
	{
		if(pwd[ft_strlen(pwd) - 1] == '/' || !ft_strcmp(pwd,"/"))
			new_ = custom_strjoin(pwd, trimmed,1);
		else
		{
			tmp = custom_strjoin(pwd, "/", 1);
			new_ = custom_strjoin(tmp, trimmed,1);
						
		}  
	}
	return (new_);
}

char	*escaped_path(char *pwd, int flag)
{
	char	*trimmed;
	int		count;
	int		lengh;

	count = (flag + 1) * 2;
	trimmed = custom_strtrim(pwd, "/..");
	if (!trimmed)
		return (NULL);
	lengh = ft_strlen(trimmed) - count;
	return (custom_strndup(trimmed, lengh, 1));
}

void	cd_deleted_path(char **right_pwd_, char *new,
							t_env_var **env_vars, int *flag)
{
	char	*new_path;

	ft_putstr_fd("cd: error retrieving current directory:", 2);
	ft_putstr_fd("getcwd: cannot access parent directories", 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	new_path = get_deleted_path_gain((*env_vars)->pwd, new);
	*right_pwd_ = new_path;
	ft_status(1);
	(*flag)++;
}
