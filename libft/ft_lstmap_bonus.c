/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:15:13 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/16 13:42:51 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstfull(t_list **lst, void *content)
{
	t_list	*node;

	if (*lst == NULL)
	{
		*lst = ft_lstnew(content);
		if (*lst == NULL)
			return (0);
	}
	else
	{
		node = ft_lstlast(*lst);
		node->next = ft_lstnew(content);
		if (node->next == NULL)
			return (0);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	void	*content;

	node = NULL;
	while (lst != NULL)
	{
		if (f != NULL)
			content = f(lst->content);
		else
			content = lst->content;
		if (!ft_lstfull(&node, content))
		{
			if (del != NULL)
				del(content);
			ft_lstclear(&node, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (node);
}
