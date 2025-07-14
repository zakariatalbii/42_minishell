/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/13 21:12:30 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_qcount(char *str)
{
	size_t	v;
	int		count;

	v = 0;
	count = 0;
	while (str[v])
	{
		if (str[v] == '\'')
		{
			v++;
			count += 2;
			while (str[v] && str[v] != '\'')
				v++;
		}
		else if (str[v] == '"')
		{
			v++;
			count += 2;
			while (str[v] && str[v] != '"')
				v++;
		}
		v++;
	}
	return (count);
}

static t_qchar	*ft_qchar_alloc(char *str)
{
	t_qchar	*qc;
	int		count;

	count = ft_qcount(str) / 2;
	qc = (t_qchar *)malloc(sizeof(t_qchar) * (count + 1));
	if (!qc)
		return (NULL);
	ft_memset(qc, 0, sizeof(t_qchar) * (count + 1));
	return (qc);
}

t_qchar	*ft_qchar(char *str, int flag)
{
	static t_qchar	*qc;

	if (flag == -1)
		return (ft_qchar_add(NULL, -1), free(qc), qc = NULL, NULL);
	else if (flag == 1)
		qc = ft_qchar_alloc(str);
	return (qc);
}

void	ft_qchar_add(char *str, int flag)
{
	t_qchar		*qc;
	static int	v;

	if (flag != -1)
		qc = ft_qchar(NULL, 0);
	if (flag == -1)
		v = 0;
	else if (flag == 0 && qc)
		qc[v].fc = str;
	else if (flag == 1 && qc)
		qc[v++].lc = str;
}
