/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:26:58 by zatalbi           #+#    #+#             */
/*   Updated: 2024/10/30 12:30:57 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	v;

	if (dst == src)
		return (dst);
	v = 0;
	while (v < n)
	{
		((unsigned char *)dst)[v] = ((const unsigned char *)src)[v];
		v++;
	}
	return (dst);
}
