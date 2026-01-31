/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:13:58 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/26 12:41:14 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(int n)
{
	size_t	count;

	count = (n <= 0);
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_cpy(char **ps, int n)
{
	if (n == INT_MIN)
	{
		ft_cpy(ps, n / 10);
		*(*ps)++ = -(n % 10) + '0';
	}
	else if (n < 0)
	{
		*(*ps)++ = '-';
		ft_cpy(ps, -n);
	}
	else if (n > 9)
	{
		ft_cpy(ps, n / 10);
		*(*ps)++ = n % 10 + '0';
	}
	else if (n >= 0 && n <= 9)
		*(*ps)++ = n + '0';
}

char	*ft_itoa(int n)
{
	size_t	count;
	char	*str;
	char	*s;

	count = ft_count(n);
	str = (char *)malloc(count + 1);
	if (!str)
		return (NULL);
	s = str;
	ft_cpy(&s, n);
	*s = '\0';
	return (str);
}
