/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:57:55 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************* show_the_tree ************* */


char	*ctype(int type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == INRED)
		return ("INRED");
	else if (type == OUTRED)
		return ("OUTRED");
	else if (type == HEREDOC)
		return ("HEREDOC");
	return ("OUTRED_A");
}

void	pfile(int red, t_file file)
{
	if (red == HEREDOC)
		printf("[%d]\n", file.fd);
	else
		printf("[%s]\n", file.name);
}

void	pcmd(char **strs)
{
	printf("[");
	while (*strs)
	{
		printf("%s", *strs++);
		if (*strs)
			printf(" ");
	}
	printf("]\n");
}

void	ptaps(int v)
{
	while (v--)
		printf("\t");
}

void	tshow(t_tree *tree, int v)
{
	if (tree->type == CMD)
	{
		printf("\n");
		ptaps(v);
		printf("(CMD)-> ");
		pcmd(tree->data.argv);
	}
	else if (tree->type == PIPE)
	{
		printf("\n");
		ptaps(v - 2);
		printf("  +-------------(PIPE)------------+\n");
		ptaps(v - 2);
		printf("  |\t\t\t\t  |\n");
		ptaps(v - 2);
		printf("  V\t\t\t\t  V\n");
		tshow(tree->data.pipe.rtree, v - 2);
		tshow(tree->data.pipe.ltree, v + 2);
	}
	else if (tree->type >= INRED)
	{
		printf("\n");
		ptaps(v);
		printf("(%s)-> ", ctype(tree->type));
		pfile(tree->type, tree->data.red.file);
		ptaps(v);
		printf("  |\n");
		ptaps(v);
		printf("  V\n");
		tshow(tree->data.red.ntree, v);
	}
}

void	show_the_tree(t_tree *tree)
{
	if (!tree)
		return ;
	tshow(tree, 10);
}

/* ***************************************** */

int	main(void)
{
	t_tree	*tree;

	tree = ft_parser("cat > $V", 1337);
	show_the_tree(tree);
	ft_free_tree(tree);
}
