/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:32:01 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/26 13:58:15 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	v;
	size_t	y;
	size_t	dstlen;
	size_t	srclen;
	size_t	size;

	srclen = ft_strlen(src);
	if (!dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	size = dstsize - dstlen;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	v = dstlen;
	y = 0;
	while (y < size - 1 && src[y])
		dst[v++] = src[y++];
	dst[v] = '\0';
	return (dstlen + srclen);
}
