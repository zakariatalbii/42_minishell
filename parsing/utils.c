/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/03 13:20:19 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_getenv(const char *name, size_t len)
{
	size_t	v;

	v = 0;
	while (__environ[v])
	{
		if (!ft_strncmp(__environ[v], name, len)
			&& __environ[v][len] == '=')
			return (ft_strchr(__environ[v], '=') + 1);
		v++;
	}
	return (NULL);
}
