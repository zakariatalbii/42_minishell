/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:27:05 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/15 11:43:59 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	v;

	v = 0;
	while (v < n && s1[v] != '\0' && s2[v] != '\0' && s1[v] == s2[v])
		v++;
	if (v == n || (unsigned char)s1[v] == (unsigned char)s2[v])
		return (0);
	else if ((unsigned char)s1[v] > (unsigned char)s2[v])
		return (1);
	return (-1);
}
