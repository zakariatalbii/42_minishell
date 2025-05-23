/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:12:09 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/16 10:13:57 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	count;
	size_t	v;

	count = 0;
	v = 0;
	while (s[v] != '\0' && s[v] == c)
		v++;
	while (s[v] != '\0')
	{
		if ((s[v] == c && s[v - 1] != c)
			|| (s[v] != c && s[v + 1] == '\0'))
			count++;
		v++;
	}
	return (count);
}

static size_t	ft_wordlen(char const **ps, char c)
{
	size_t	len;

	len = 0;
	while (**ps != '\0' && **ps == c)
		(*ps)++;
	while (**ps != '\0' && **ps != c)
	{
		len++;
		(*ps)++;
	}
	return (len);
}

static void	ft_wordcpy(char *s, char const **ps, char c)
{
	size_t	v;

	while (**ps != '\0' && **ps == c)
		(*ps)++;
	v = 0;
	while (**ps != '\0' && **ps != c)
	{
		s[v++] = **ps;
		(*ps)++;
	}
	s[v] = '\0';
}

static size_t	ft_wordall(char **strs, size_t count, char const *s, char c)
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
		if (strs[v] == NULL)
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

	if (s == NULL)
		return (NULL);
	count = ft_countwords(s, c);
	strs = (char **)malloc((count + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	l = ft_wordall(strs, count, s, c);
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
