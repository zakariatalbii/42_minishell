/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:13:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/10 23:02:32 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countdigits(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_cpydigits(char **ps, int n)
{
	if (n == -2147483648)
	{
		ft_cpydigits(ps, n / 10);
		*(*ps)++ = -(n % 10) + '0';
	}
	else if (n < 0)
	{
		*(*ps)++ = '-';
		ft_cpydigits(ps, -n);
	}
	else if (n > 9)
	{
		ft_cpydigits(ps, n / 10);
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

	count = ft_countdigits(n);
	str = (char *)malloc(count + 1);
	if (str == NULL)
		return (NULL);
	s = str;
	ft_cpydigits(&s, n);
	*s = '\0';
	return (str);
}
