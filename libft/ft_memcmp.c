/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:35:36 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/13 15:31:41 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	v;

	v = 0;
	while (v < n
		&& ((const unsigned char *)s1)[v] == ((const unsigned char *)s2)[v])
		v++;
	if (v == n)
		return (0);
	return ((int)(((const unsigned char *)s1)[v]
				- ((const unsigned char *)s2)[v]));
}
