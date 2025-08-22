/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:23:52 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/13 01:20:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_exerv(t_tree *tree,
		t_env **environ, t_env_var **env_vars)
{
	int	pid;
	int	status_1;

	pid = fork();
	error_handling(pid, "close", NULL);
	if (pid < 0)
	{
		kill_zombies(env_vars);
		ft_status(1);
		exit(ft_status(-1));
	}
	if (pid > 0)
		add_to_trsh_pid(pid, env_vars);
	ft_signals(-1);
	if (pid == 0)
	{
		ft_signals(0);
		ft_store_fds(-1);
		external_commands_execution(tree->data.argv, environ, env_vars);
	}
	waitpid(pid, &status_1, 0);
	status_handling(status_1);
}

int	outfiles_checking(t_tree *tree)
{
	int	fd;

	if (tree->type == 3)
	{
		fd = open(tree->data.red.file.name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			error_handling(-1, "open", tree->data.red.file.name);
			return (1);
		}
		close(fd);
	}
	else if (tree->type == 5)
	{
		fd = open(tree->data.red.file.name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			error_handling(-1, "open", tree->data.red.file.name);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	recursive_check(t_tree *tree)
{
	int	fd;

	while (tree)
	{
		if (tree->type >= 2 && tree->type <= 5)
		{
			if (tree->type == 2)
			{
				fd = open(tree->data.red.file.name, O_RDONLY);
				if (fd < 0)
				{
					error_handling(-1, "open", tree->data.red.file.name);
					return (1);
				}
				close(fd);
			}
			else
				return (outfiles_checking(tree));
			tree = tree->data.red.ntree;
		}
		else
			break ;
	}
	return (0);
}
