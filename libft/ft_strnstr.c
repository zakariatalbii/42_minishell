/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:21:57 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/21 11:47:17 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	v;
	size_t	y;

	v = 0;
	while (v < len
		&& haystack[v] != '\0')
	{
		y = 0;
		while (v + y < len && needle[y] != '\0' && needle[y] == haystack[v + y])
			y++;
		if (needle[y] == '\0')
			return ((char *)(haystack + v));
		v++;
	}
	if ((*needle == '\0' && *haystack == '\0')
		|| (len == 0 && *needle == '\0'))
		return ((char *)haystack);
	return (NULL);
}
