/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/08/06 22:59:38 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_lines(int flag)
{
	static int	count;

	if (flag)
		count++;
	return (count);
}

int	ft_status(int s)
{
	static int	status;

	if (s >= 0)
		return (status = s, 1);
	return (status);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	v;

	v = 0;
	if(!s1 || !s2)
		return(-1);
	while (s1[v] && s2[v] && s1[v] == s2[v])
		v++;
	if (s1[v] == s2[v])
		return (0);
	else if (s1[v] > s2[v])
		return (1);
	return (-1);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	size;
	char	*str;

	if (!s1 || !n)
		return (NULL);
	size = ft_strlen(s1);
	if (size > n)
		size = n;
	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size + 1);
	return (str);
}

char	*ft_strsjoin(char **strs)
{
	char	*str;
	size_t	len;
	size_t	v;

	if (!strs || !*strs)
		return (NULL);
	v = 0;
	len = 0;
	while (strs[v])
		len += ft_strlen(strs[v++]);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, len + 1);
	v = 0;
	while (strs[v])
		ft_strlcat(str, strs[v++], len + 1);
	return (str);
}
