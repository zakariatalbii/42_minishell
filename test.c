/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/21 06:10:37 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_the_tree(t_tree *tree);

int	main(void)
{
	t_tree	*tree;
	char *line;
	static char *PWD;
	static char *OLDPWD;
	char	*prompt;
	static int *status;

    if(!status)
    {
        status = malloc(sizeof(int));
        *status = 0;
    }
	PWD = getcwd(NULL,0);
	OLDPWD = getenv("OLDPWD");
	
	while (1)
	{	
		prompt = ft_strjoin(PWD, "> ");
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		tree = ft_parser(line, 1337);
		show_the_tree(tree);
		recursion(tree,&PWD,&OLDPWD, status);
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	exit(0);
}
