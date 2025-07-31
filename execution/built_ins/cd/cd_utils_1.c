/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:30:50 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 03:29:49 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_deleted_path_gain(char *PWD, char *new)
{
	char	*deleted_path;
	char	*new_;
	char	*pwd_for_path;

	pwd_for_path = custom_strjoin(PWD, "/", 1);
	if (!pwd_for_path)
		return (NULL);
	new_ = custom_strtrim(new, "/");
	deleted_path = custom_strjoin(pwd_for_path, new_, 1);
	if (!deleted_path)
		return (NULL);
	else
		return (deleted_path);
}

char	*go_backwards(char *pwd)
{
	int		i;
	int		lengh;
	char	*path;
	int		count;

	if (!pwd)
		return (NULL);
	(1 && (lengh = count_words(pwd, '/')), (count = 0), (i = -1));
	if (!ft_strcmp(pwd, "/"))
		path = custom_strdup(pwd, 1);
	else
	{
		while (pwd[++i] && count < lengh)
		{
			if (pwd[i] == '/')
			{
				count++;
			}
		}
		if (i == 1)
			path = custom_strndup(pwd, i, 1);
		else
			path = custom_strndup(pwd, i - 1, 1);
	}
	return (path);
}

int	count_two_points(char *new)
{
	int		count;
	char	*haystack;

	count = 0;
	haystack = ft_strnstr(new, "..", ft_strlen(new));
	if (!haystack)
		return (0);
	count++;
	while (haystack)
	{
		haystack = ft_strnstr(new + 2, "..", ft_strlen(new));
		if (haystack)
			count++;
		new = haystack;
	}
	return (count);
}

void	cd_points_handling(char **right_pwd, char *new, char *pwd)
{
	int	count;

	if (!ft_strncmp(new, ".", 1))
	{
		count = count_two_points(new);
		if (count >= 1)
		{
			while (count)
			{
				*right_pwd = go_backwards(pwd);
				pwd = *right_pwd;
				count --;
			}
		}
		else
			*right_pwd = pwd;
	}
}

char	*right_pwd(t_env **environ, char *new, t_env_var **env_vars)
{
	char	*right_pwd;
	char	*pwd;
	char	*tmp;
	int		count;

	(1 && (pwd = (*env_vars)->pwd), (right_pwd = NULL));
	if (pwd && new)
	{
		if (!ft_strncmp(new, ".", 1))
			cd_points_handling(&right_pwd, new, pwd);
		else
		{
			if (new[0] == '/')
				right_pwd = trim_back_slach(new);
			else
			{
				tmp = trim_back_slach(new);
				if (tmp)
					right_pwd = custom_strjoin(pwd, tmp, 1);
			}
		}
		return (right_pwd);
	}
	return (NULL);
}
