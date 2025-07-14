/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/14 18:07:01 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_inqchar(char *str)
{
	t_qchar	*qc;
	int		v;

	qc = ft_qchar(NULL, 0);
	v = 0;
	while (qc && qc[v].fc && qc[v].lc)
	{
		if (str >= qc[v].fc && str < qc[v].lc)
			return (1);
		v++;
	}
	return (0);
}

static size_t	ft_ignore_spaces(char *str)
{
	size_t	v;

	v = 0;
	while (((str[v] >= 9 && str[v] <= 13) || str[v] == 32)
		&& !ft_inqchar(&str[v]))
		v++;
	return (v);
}

static size_t	ft_count(char *str)
{
	size_t	v;

	v = 0;
	while (str[v] && (!ft_isspace(str[v]) || ft_inqchar(&str[v])))
		v++;
	return (v);
}

t_list	*ft_tokenlst(char *str)
{
	t_list	*head;
	t_list	*node;
	size_t	count;

	head = NULL;
	str += ft_ignore_spaces(str);
	if (!*str)
	{
		node = ft_lstnew(ft_new_token(ft_strdup(str)));
		ft_lstadd_back(&head, node);
		if (!node || !node->content)
			return (ft_lstclear(&head, ft_free_token), perror("malloc"),
				ft_status(1), NULL);
	}
	while (*str)
	{
		count = ft_count(str);
		node = ft_lstnew(ft_new_token(ft_strndup(str, count)));
		ft_lstadd_back(&head, node);
		if (!node || !node->content)
			return (ft_lstclear(&head, ft_free_token), perror("malloc"),
				ft_status(1), NULL);
		str += ft_ignore_spaces(str + count) + count;
	}
	return (head);
}
