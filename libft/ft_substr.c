/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:45:21 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/15 14:05:07 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
