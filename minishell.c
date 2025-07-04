/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/04 21:12:16 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_the_tree(t_tree *tree);// for test

static char	*ft_readline(void)
{
	char	*line;
	char	*prompt;
	char	*cwd;

	cwd = ft_getenv("PWD");
	if (!cwd)
	{
		cwd = getcwd(NULL, 0);
		prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
	}
	else
		prompt = ft_strjoin(cwd, "$ ");
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

	ft_signals(1);
	if (!ft_environ(ft_envinit(), 1))
		exit (1);
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		tree = ft_parser(line, ft_status(-1));
		show_the_tree(tree);// for test
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	ft_environ_clear();
	exit(ft_status(-1));
}
