/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:36:04 by zatalbi           #+#    #+#             */
/*   Updated: 2025/08/10 11:49:58 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	ft_split_clear(char **strs)
{
	char	**tmp;

	if (!strs)
		return ;
	tmp = strs;
	while (*tmp)
		free(*tmp++);
	free(strs);
}

static int	ft_path_alloc(char **path, char ***strs,
		char *str, t_env_var **env_vars)
{
	if (*str == '/')
		*path = ft_strdup("/");
	else
		*path = ft_strdup((*env_vars)->pwd);
	if (*path)
		*strs = ft_split(str, '/');
	if (!*path || !*strs)
		return (free(*path), -1);
	return (0);
}

static size_t	ft_size(char *path)
{
	char	*s;

	s = ft_strrchr(path, '/');
	return (s - path + (s == path));
}

char	*ft_path_init(char *str, t_env_var **env_vars)
{
	struct stat	stat;
	char		**strs;
	char		*path;
	char		*tmp;
	int			v;

	v = -1;
	if (ft_path_alloc(&path, &strs, str, env_vars))
		return (NULL);
	while (strs[++v] && !lstat(path, &stat))
	{
		tmp = path;
		if (!ft_strcmp(strs[v], "."))
			continue ;
		else if (!ft_strcmp(strs[v], ".."))
			path = ft_strndup(path, ft_size(path));
		else
			path = ft_strsjoin((char *[]){path, "/", strs[v], NULL});
		free(tmp);
		if (!path)
			break ;
	}
	if (lstat(path, &stat))
		return (ft_split_clear(strs), free(path), NULL);
	return (ft_split_clear(strs), path);
}
