/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strndup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:05:44 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/25 03:02:33 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*custom_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	v;
	char	*str;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	v = slen - start;
	if (v > slen || v == 0)
	{
		len = 0;
		start = 0;
	}
	if (v < len)
		len = v;
	str = (char *)gc_malloc(len + 1,1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
char	*custom_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	while (s1 && set && s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = 0;
	if (s1)
		end = ft_strlen(s1);
	while (s1 && set && end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (custom_substr(s1, (unsigned int)start, end - start));
}
char	*custom_strndup(const char *s1, size_t n, int pid)
{
	size_t	size;
	char	*str;

	if (!s1 || !n)
		return (NULL);
	size = ft_strlen(s1);
	if (size > n)
		size = n;
	str = (char *)gc_malloc(size + 1,1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size + 1);
	return (str);
}