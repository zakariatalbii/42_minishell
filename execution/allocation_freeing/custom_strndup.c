/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strndup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:05:44 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/10 22:20:11 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*custom_strndup(const char *s1, size_t n, int pid)
{
	size_t	size;
	char	*str;

	if (!s1 || !n)
		return (NULL);
	size = ft_strlen(s1);
	if (size > n)
		size = n;
	str = (char *)gc_malloc(size + 1,1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size + 1);
	return (str);
}