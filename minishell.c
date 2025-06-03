/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/03 16:31:47 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_the_tree(t_tree *tree);// for test

static char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_strjoin(getenv("PWD"), "$ ");
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (free(prompt), ft_count_lines(1), line);
}

int	main(void)
{
	t_tree	*tree;
	char	*line;
	static char *PWD;
	static char *OLDPWD;
	char	*prompt;

	
	PWD = ft_strdup(PWD_);
	OLDPWD = ft_strdup(OLDPWD_);
	ft_signals(1);
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		tree = ft_parser(line, ft_status(-1));
		show_the_tree(tree);// for test
		recursion(tree,&PWD,&OLDPWD);
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	exit(ft_status(-1));
}
