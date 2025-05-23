/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:27 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/09 14:39:46 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + 1;
	str = (char *)malloc(size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size);
	return (str);
}
