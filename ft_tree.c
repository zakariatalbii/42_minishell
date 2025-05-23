/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:44:30 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tree	*ft_red_tree(t_list *lst, t_tree *tree, int status, int *flag)
{
	t_file	file;

	while (tree && lst && ((t_token *)lst->content)->type != PIPE)
	{
		if (((t_token *)lst->content)->type >= INRED)
		{
			if (((t_token *)lst->content)->type == HEREDOC)
			{
				file.fd = ft_heredoc(&((t_token *)lst->next->content)->token,
						status, *flag);
				if (file.fd == -1)
					return (ft_free_tree(tree), NULL);
				*flag = 0;
			}
			else
				file.name = ((t_token *)lst->next->content)->token;
			((t_token *)lst->next->content)->token = NULL;
			return (ft_red_node(((t_token *)lst->content)->type, file,
					ft_red_tree(lst->next->next, tree, status, flag)));
		}
		lst = lst->next;
	}
	return (tree);
}

static t_tree	*ft_pipe_tree(t_list *lst, t_tree *tree, int status, int *flag)
{
	while (tree && lst)
	{
		if (((t_token *)lst->content)->type == PIPE)
			return (ft_pipe_node(tree, ft_tree(lst->next, status, *flag)));
		lst = lst->next;
	}
	return (tree);
}

t_tree	*ft_tree(t_list *lst, int status, int flag)
{
	t_tree	*tree;

	if (!lst)
		return (NULL);
	tree = ft_pipe_tree(lst,
			ft_red_tree(lst, ft_cmd_node(ft_argv(lst)),
				status, &flag), status, &flag);
	return (tree);
}
