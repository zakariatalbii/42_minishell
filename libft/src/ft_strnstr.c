/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:21:57 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/26 14:29:17 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	v;
	size_t	y;

	v = 0;
	while (v < len && haystack[v])
	{
		y = 0;
		while (v + y < len && needle[y] && needle[y] == haystack[v + y])
			y++;
		if (!needle[y])
			return ((char *)(haystack + v));
		v++;
	}
	if ((!*needle && !*haystack) || (!len && !*needle))
		return ((char *)haystack);
	return (NULL);
}
