/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:41:34 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lexer(char *line, int status)
{
	t_list	*head;

	head = ft_split_line(line);
	ft_check_tokens(&head);
	ft_expand_tokens(&head, status);
	return (head);
}

t_tree	*ft_parser(char *line, int status)
{
	t_tree	*tree;
	t_list	*lst;

	lst = ft_lexer(line, status);
	tree = ft_tree(lst, status, 1);
	ft_lstclear(&lst, ft_free_token);
	return (tree);
}
