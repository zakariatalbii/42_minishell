/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:52:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 09:19:55 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*custom_strdup(const char	*s1, int pid)
{
	char	*ptr;

	ptr = (char *)gc_malloc(ft_strlen(s1) + 1, pid);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr = ft_memcpy(ptr, s1, ft_strlen(s1));
	ptr[ft_strlen(s1)] = '\0';
	return (ptr);
}

static	void	loop_copying_s2(const char *s2, char **ptr, int count)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		(*ptr)[count] = s2[i];
		i++;
		count++;
	}
	(*ptr)[count] = '\0';
}

char	*custom_strjoin(const char *s1, const char *s2, int pid)
{
	char	*ptr;
	size_t	i;
	size_t	count;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return (custom_strdup(s2, pid));
	if (!s2)
		return (custom_strdup(s1, pid));
	ptr = (char *)gc_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, pid);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	count = i;
	loop_copying_s2(s2, &ptr, count);
	return (ptr);
}
