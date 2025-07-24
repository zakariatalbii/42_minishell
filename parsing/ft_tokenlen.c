/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/24 03:42:27 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_numlen(int nb)
{
	size_t	count;

	count = 1;
	if (nb < 0)
		count++;
	while (nb / 10 && ++count)
		nb /= 10;
	return (count);
}

static size_t	ft_envlen(char *str, size_t *count, int flag)
{
	size_t	v;
	char	*env;

	v = 0;
	if (str[v] == '$')
		return (*count += 2, 1);
	else if (((!ft_isalnum(str[v]) && str[v] != '_' && ((str[v] != '\''
						&& str[v] != '"') || flag == 0b10))
			|| (flag == 0b01 && (ft_isalnum(str[v]) || str[v] == '_')))
		&& ++(*count))
		return (0);
	if ((flag | 0b10) == 0b10 && ft_isalnum(str[v]))
		v++;
	else
		while ((flag | 0b10) == 0b10 && (ft_isalnum(str[v]) || str[v] == '_'))
			v++;
	env = ft_getlenv(str, v);
	if (env)
		*count += ft_strlen(env);
	return (v);
}

static size_t	ft_qcase(char *str, size_t *count)
{
	size_t	v;

	v = 0;
	while (str[++v] != '\'')
		(*count)++;
	return (v);
}

static size_t	ft_dqcase(char *str, size_t *count, int status, int flag)
{
	size_t	v;

	v = 0;
	while (str[++v] != '"')
	{
		if (!flag && str[v] == '$')
		{
			if (str[++v] == '"' && --v)
				(*count)++;
			else if (str[v] == '?')
				*count += ft_numlen(status);
			else
				v += ft_envlen(&str[v], count, 0) - 1;
		}
		else
			(*count)++;
	}
	return (v);
}

size_t	ft_tokenlen(char *str, int status, int flag)
{
	size_t	v;
	size_t	count;

	v = 0;
	count = 0;
	while (str[v])
	{
		if ((flag | 0b01) == 0b01 && str[v] == '\'')
			v += ft_qcase(&str[v], &count);
		else if ((flag | 0b01) == 0b01 && str[v] == '"')
			v += ft_dqcase(&str[v], &count, status, flag);
		else if ((flag | 0b10) == 0b10 && str[v] == '$' && str[v + 1] == '?'
			&& ++v)
			count += ft_numlen(status);
		else if (str[v] == '$' && ++v)
			v += ft_envlen(&str[v], &count, flag) - 1;
		else
			count++;
		if (str[v])
			v++;
	}
	return (count);
}
