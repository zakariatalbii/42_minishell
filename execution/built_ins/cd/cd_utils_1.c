/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:30:50 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/02 22:23:07 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

// int	count_two_points(char *new)
// {
// 	int		count;
// 	char	*haystack;

// 	count = 0;
// 	haystack = ft_strnstr(new, "..", ft_strlen(new));
// 	if (!haystack)
// 		return (0);
// 	count++;
// 	while (haystack)
// 	{
// 		haystack = ft_strnstr(new + 2, "..", ft_strlen(new));
// 		if (haystack)
// 			count++;
// 		new = haystack;
// 	}
// 	return (count);
// }

// void	cd_points_handling(char **right_pwd, char *new, char *pwd)
// {
// 	int	count;

// 	if (!ft_strncmp(new, ".", 1))
// 	{
// 		count = count_two_points(new);
// 		if (count >= 1)
// 		{
// 			while (count)
// 			{
// 				*right_pwd = go_backwards(pwd);
// 				pwd = *right_pwd;
// 				count --;
// 			}
// 		}
// 		else
// 			*right_pwd = pwd;
// 	}
// }


char	*right_pwd(char *new, t_env_var **env_vars)
{
	char	*right_pwd;
	char	**splited;
	char	*pwd;
	int 	i;
	
	i = 0;
	(1 && (pwd = (*env_vars)->pwd), (right_pwd = pwd));
	if (pwd && new)
	{
		splited = custom_split(new, '/', 1);
		if(!splited[0])
			return(custom_strdup("/", 1));
		while(splited[i])
		{
			if(!ft_strncmp(splited[i], "..", 2))
			{
				if(!ft_strcmp(right_pwd,"/"))
					return(right_pwd);
				right_pwd = go_backwards(right_pwd);
			}
			else if(!ft_strncmp(splited[i], ".", 1))
			{
				i++;
				continue;
			}
			else
				right_pwd = trim_back_slach(splited[i], right_pwd);
			i++;
		}
		return (right_pwd);
	}
	return (NULL);
}
