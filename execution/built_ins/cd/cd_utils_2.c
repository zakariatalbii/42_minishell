/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:39:07 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/01 23:52:47 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	cd_flag(int flag_)
{
	static int	flag;

	if (flag_)
	{
		if (!ft_getenv("PWD"))
			flag++;
		if (ft_getenv("PWD") && flag)
			flag = 0;
		return (flag);
	}
	else
		return (flag);
}

void	pwdinf_update(t_env_var **env_vars, char *path)
{
	if (cd_flag(0) == 1)
	{
		ft_unsetenv("OLDPWD");
		ft_setenv("OLDPWD", NULL, 0);
	}
	else
	{
		if (ft_getenv("PWD"))
			ft_setenv("OLDPWD", ft_getenv("PWD"), 0);
		else
			ft_setenv("OLDPWD", (*env_vars)->pwd, 0);
	}
	if (ft_getenv("PWD"))
		ft_setenv("PWD", path, 0);
	(*env_vars)->pwd = custom_strdup(path, 1);
}

char	*trim_back_slach(char *new)
{
	char	*trimmed;
	char	*new_;

	trimmed = custom_strtrim(new, "/");
	new_ = custom_strjoin("/", trimmed, 1);
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
