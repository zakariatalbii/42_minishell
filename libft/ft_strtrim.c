/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:11:09 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/21 15:15:47 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
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
	return (ft_substr(s1, (unsigned int)start, end - start));
}
