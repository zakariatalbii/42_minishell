/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:38:20 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_argv(char **argv)
{
	char	**strs;

	if (!argv)
		return ;
	strs = argv;
	while (*strs)
		free(*strs++);
	free(argv);
}

void	ft_free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == CMD)
	{
		ft_free_argv(tree->data.argv);
		free(tree);
	}
	else if (tree->type == PIPE)
	{
		ft_free_tree(tree->data.pipe.rtree);
		ft_free_tree(tree->data.pipe.ltree);
		free(tree);
	}
	else if (tree->type >= INRED)
	{
		ft_free_tree(tree->data.red.ntree);
		if (tree->type != HEREDOC)
			free(tree->data.red.file.name);
		free(tree);
	}
}
