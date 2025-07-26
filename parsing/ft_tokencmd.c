/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:13:58 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/26 20:47:02 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_cmd(t_list *lst)
{
	while (lst && ((t_token *)lst->content)->type != PIPE)
	{
		if (((t_token *)lst->content)->type >= INRED)
		{
			lst = lst->next->next;
			continue ;
		}
		return (((t_token *)lst->content)->token);
	}
	return (NULL);
}

char	*ft_tokencmd(t_list *lst, t_list *head)
{
	char	*str;

	str = ft_cmd(lst);
	while (lst)
	{
		if (((t_token *)lst->content)->type == PIPE)
			str = ft_cmd(lst->next);
		if (lst == head)
			break ;
		lst = lst->next;
	}
	return (str);
}
