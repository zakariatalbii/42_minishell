/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:03:00 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/26 13:43:46 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	v;

	v = 0;
	while (s[v])
	{
		if (s[v] == (char)c)
			return ((char *)(s + v));
		v++;
	}
	if (!(char)c)
		return ((char *)(s + v));
	return (NULL);
}
