/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:12:09 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/26 14:19:19 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	count;
	size_t	v;

	count = 0;
	v = 0;
	while (s[v] && s[v] == c)
		v++;
	while (s[v])
	{
		if ((s[v] == c && s[v - 1] != c) || (s[v] != c && !s[v + 1]))
			count++;
		v++;
	}
	return (count);
}

static size_t	ft_wordlen(char const **ps, char c)
{
	size_t	len;

	len = 0;
	while (**ps && **ps == c)
		(*ps)++;
	while (**ps && **ps != c)
	{
		len++;
		(*ps)++;
	}
	return (len);
}

static void	ft_wordcpy(char *s, char const **ps, char c)
{
	size_t	v;

	while (**ps && **ps == c)
		(*ps)++;
	v = 0;
	while (**ps && **ps != c)
	{
		s[v++] = **ps;
		(*ps)++;
	}
	s[v] = '\0';
}

static size_t	ft_wordalloc(char **strs, size_t count, char const *s, char c)
{
	size_t		v;
	size_t		len;
	char const	*s1;
	char const	*s2;

	s1 = s;
	v = 0;
	while (v < count)
	{
		s2 = s1;
		len = ft_wordlen(&s1, c);
		strs[v] = (char *)malloc(len + 1);
		if (!strs[v])
			return (v);
		ft_wordcpy(strs[v++], &s2, c);
	}
	strs[v] = NULL;
	return (v);
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	size_t		v;
	size_t		l;
	char		**strs;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	strs = (char **)malloc((count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	l = ft_wordalloc(strs, count, s, c);
	if (l < count)
	{
		v = 0;
		while (v < l)
			free(strs[v++]);
		free(strs);
		return (NULL);
	}
	return (strs);
}
