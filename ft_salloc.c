/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_salloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:58:34 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/07 17:59:37 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	**ft_slst(void)
{
	static t_list	*lst;

	return (&lst);
}

void	*ft_salloc(void *ptr)
{
	t_list	*node;

	if (ptr)
		node = ft_lstnew(ptr);
	if (!ptr || !node)
		return (ft_lstclear(ft_slst(), free), free(ptr), NULL);
	ft_lstadd_back(ft_slst(), node);
	return (ptr);
}

void	ft_sfree(void *ptr)
{
	t_list	**slst;
	t_list	*lst;
	t_list	*tmp;

	slst = ft_slst();
	lst = *slst;
	if (lst && lst->content == ptr)
	{
		*slst = lst->next;
		free(lst->content);
		free(lst);
		return ;
	}
	while (lst)
	{
		tmp = lst->next;
		if (tmp && tmp->content == ptr)
		{
			lst->next = tmp->next;
			free(tmp->content);
			free(tmp);
			return ;
		}
		lst = lst->next;
	}
}
