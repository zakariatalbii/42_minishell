/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:14:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/13 01:19:22 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	kill_zombies(t_env_var **env_vars)
{
	t_pid_trash	*trsh;
	int			status;

	trsh = (*env_vars)->pid_trash;
	while (trsh)
	{
		if (trsh->pid != 1)
		{
			kill(trsh->pid, SIGKILL);
			waitpid(trsh->pid, &status, 0);
		}
		trsh = trsh->next;
	}
}

void	add_to_trsh_pid(pid_t pid, t_env_var **env_vars)
{
	t_pid_trash	*new;

	new = gc_malloc(sizeof(t_pid_trash), 1);
	if (!new)
		return ;
	(new->pid) = pid ;
	new->next = (*env_vars)->pid_trash;
	(*env_vars)->pid_trash = new;
}

static void	child_1(int *fd, t_tree *tree, t_env_var **env_vars, t_env **env)
{
	if (*((*env_vars)->pid) > 0)
		add_to_trsh_pid(*((*env_vars)->pid), env_vars);
	if (*((*env_vars)->pid) == -1)
	{
		kill_zombies(env_vars);
		ft_status(1);
		exit(ft_status(-1));
	}
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

static void	child_2(int *fd, t_tree *tree, t_env_var **env_vars, t_env **env)
{
	int	status;

	if (*((*env_vars)->pid_2) > 0)
		add_to_trsh_pid(*((*env_vars)->pid_2), env_vars);
	if (*((*env_vars)->pid_2) == -1)
	{
		if (*((*env_vars)->pid) > 0)
			waitpid(*((*env_vars)->pid), &status, 0);
		kill_zombies(env_vars);
		ft_status(1);
		exit(ft_status(-1));
	}
	if (*((*env_vars)->pid_2) == 0)
	{
		ft_signals(0);
		error_handling(close(fd[1]), "close", NULL);
		error_handling(dup2(fd[0], STDIN_FILENO), "dup2", NULL);
		error_handling(close(fd[0]), "close", NULL);
		recursion(tree->data.pipe.ltree, env, env_vars);
		(ft_store_fds(-1), exit(ft_status(-1)));
	}
}

void	pipe_line(t_tree *tree,
		t_env_var **env_vars, t_env **env)
{
	int	fd[2];
	int	pid[2];
	int	status[2];

	if (pipe(fd) == -1)
	{
		kill_zombies(env_vars);
		ft_status(1);
		exit(ft_status(-1));
	}
	pid[0] = fork();
	(error_handling(pid[0], "fork", NULL), ft_signals(-1));
	*((*env_vars)->pid) = pid[0];
	child_1(fd, tree, env_vars, env);
	pid[1] = fork();
	(error_handling(pid[1], "fork", NULL), ft_signals(-1));
	*((*env_vars)->pid_2) = pid[1];
	child_2(fd, tree, env_vars, env);
	error_handling(close(fd[0]), "close", NULL);
	error_handling(close(fd[1]), "close", NULL);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	status_handling_chid(status[1]);
}
