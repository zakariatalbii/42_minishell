/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:14:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/02 00:58:33 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_1(int *fd, t_tree *tree, t_env_var **env_vars, t_env **env)
{
	if (*((*env_vars)->pid) == 0)
	{
		ft_signals(0);
		error_handling(close(fd[0]), "close", NULL);
		error_handling(dup2(fd[1], STDOUT_FILENO), "dup2", NULL);
		error_handling(close(fd[1]), "close", NULL);
		recursion(tree->data.pipe.rtree, env, env_vars);
		ft_store_fds(-1);
		exit(ft_status(-1));
	}
}

static void	pipe_line(t_tree *tree, t_env **environ,
		t_env_var **env_vars, t_env **env)
{
	int	fd[2];
	int	pid[2];
	int	status[2];

	pipe(fd);
	(1 && (pid[0] = fork()),
		(error_handling(pid[0], "fork", NULL)), (ft_signals(-1)));
	*((*env_vars)->pid) = pid[0];
	child_1(fd, tree, env_vars, env);
	(1 && (pid[1] = fork()),
		(error_handling(pid[1], "fork", NULL)), ft_signals(-1));
	if (pid[1] == 0)
	{
		ft_signals(0);
		error_handling(close(fd[1]), "close", NULL);
		error_handling(dup2(fd[0], STDIN_FILENO), "dup2", NULL);
		error_handling(close(fd[0]), "close", NULL);
		recursion(tree->data.pipe.ltree, environ, env_vars);
		(ft_store_fds(-1), exit(ft_status(-1)));
	}
	error_handling(close(fd[0]), "close", NULL);
	error_handling(close(fd[1]), "close", NULL);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	status_handling_chid(pid, fd, status[1], status[0]);
}

static void	command_execution(t_tree *tree,
		t_env **environ, int flag, t_env_var **env_vars)
{
	int	pid;
	int	status_1;

	if (is_built_in(tree->data.argv) == 1)
	{
		if (flag == 1)
			flag = 0;
		else if (flag == 0)
			flag = 1;
		execute_the_builtin(tree, environ, env_vars, flag);
	}
	else
	{
		if (!invalid_commands_checking(tree->data.argv[0], environ, env_vars))
			return ;
		1 && (pid = fork()), (error_handling(pid, "close", NULL));
		ft_signals(-1);
		if (pid == 0)
		{
			ft_signals(0);
			ft_store_fds(-1);
			external_commands_execution(tree->data.argv, environ, env_vars);
		}
		(1 && (waitpid(pid, &status_1, 0)), (status_handling(status_1)));
	}
}

static void	redirection(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
	if (tree->type >= 2 && tree->type <= 5)
	{
		if (recursive_check(tree))
			return ;
		else if (tree->type == 2)
			infile_handling(tree, environ, env_vars);
		else if (tree->type == 3)
			outfile_handling(tree, environ, env_vars);
		else if (tree->type == 4)
			heredoc_handling(tree, environ, env_vars);
		else if (tree->type == 5)
			append_handling(tree, environ, env_vars);
	}
}

void	recursion(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
	static int	flag;

	if (!tree)
		return ;
	if (tree->type == 0 && tree->data.argv && tree->data.argv[0])
	{
		last_command_arg(tree, environ);
		command_execution(tree, environ, flag, env_vars);
	}
	else if (tree->type == 1)
	{
		flag = 1;
		pipe_line(tree, environ, env_vars, environ);
	}
	redirection(tree, environ, env_vars);
}
