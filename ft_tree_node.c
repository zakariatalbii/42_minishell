/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:43:40 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_argc(t_list *lst)
{
	t_list	*head;
	size_t	count;

	head = lst;
	count = 0;
	while (head && ((t_token *)head->content)->type != PIPE)
	{
		if (((t_token *)head->content)->type >= INRED)
		{
			head = head->next->next;
			continue ;
		}
		count++;
		head = head->next;
	}
	return (count);
}

char	**ft_argv(t_list *lst)
{
	t_list	*head;
	char	**argv;
	size_t	v;

	if (!lst)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (ft_argc(lst) + 1));
	if (!argv)
		return (perror("malloc"), NULL);
	head = lst;
	v = 0;
	while (head && ((t_token *)head->content)->type != PIPE)
	{
		if (((t_token *)head->content)->type >= INRED)
		{
			head = head->next->next;
			continue ;
		}
		argv[v++] = ((t_token *)head->content)->token;
		((t_token *)head->content)->token = NULL;
		head = head->next;
	}
	argv[v] = NULL;
	return (argv);
}

t_tree	*ft_cmd_node(char **argv)
{
	t_tree	*tree;

	if (!argv)
		return (NULL);
	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (perror("malloc"), ft_free_argv(argv), NULL);
	tree->type = CMD;
	tree->data.argv = argv;
	return (tree);
}

t_tree	*ft_red_node(int type, t_file file, t_tree *ntree)
{
	t_tree	*tree;

	if (ntree)
		tree = (t_tree *)malloc(sizeof(t_tree));
	if (!ntree || !tree)
	{
		if (type != HEREDOC)
			free(file.name);
		if (!ntree)
			return (NULL);
		return (perror("malloc"), ft_free_tree(ntree), NULL);
	}
	tree->type = type;
	tree->data.red.file = file;
	tree->data.red.ntree = ntree;
	return (tree);
}

t_tree	*ft_pipe_node(t_tree *rtree, t_tree *ltree)
{
	t_tree	*tree;

	if (!rtree || !ltree)
		return (ft_free_tree(rtree), ft_free_tree(ltree), NULL);
	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (perror("malloc"), ft_free_tree(rtree), ft_free_tree(ltree),
			NULL);
	tree->type = PIPE;
	tree->data.pipe.rtree = rtree;
	tree->data.pipe.ltree = ltree;
	return (tree);
}
