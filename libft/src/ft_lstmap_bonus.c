/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:15:13 by zatalbi           #+#    #+#             */
/*   Updated: 2026/01/26 12:57:07 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstfull(t_list **lst, void *content)
{
	t_list	*node;

	if (!*lst)
	{
		*lst = ft_lstnew(content);
		if (!*lst)
			return (0);
	}
	else
	{
		node = ft_lstlast(*lst);
		node->next = ft_lstnew(content);
		if (!node->next)
			return (0);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	void	*content;

	node = NULL;
	while (lst)
	{
		if (f)
			content = f(lst->content);
		else
			content = lst->content;
		if (!ft_lstfull(&node, content))
		{
			if (del)
				del(content);
			ft_lstclear(&node, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (node);
}
