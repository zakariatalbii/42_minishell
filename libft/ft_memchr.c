/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:18:01 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/09 14:06:28 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	v;

	v = 0;
	while (v < n)
	{
		if (((const unsigned char *)s)[v] == (unsigned char)c)
			return ((void *)(s + v));
		v++;
	}
	return (NULL);
}
