/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/13 01:12:49 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(char **command)
{
	if (command)
	{
		if (!command[0])
			return (0);
		if ((!ft_strcmp(command[0], "echo"))
			|| (!ft_strcmp(command[0], "cd")) || (!ft_strcmp(command[0], "pwd"))
			|| (!ft_strcmp(command[0], "export"))
			|| (!ft_strcmp(command[0], "unset")
				|| (!ft_strcmp(command[0], "env"))
				|| (!ft_strcmp(command[0], "exit"))))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	execute_the_builtin(t_tree *tree,
	t_env **s_environ, t_env_var **env_vars, int pid)
{
	char	**command;

	command = tree->data.argv;
	if (!ft_strcmp(command[0], "echo"))
		echo_execution(command);
	else if (!ft_strcmp(command[0], "cd"))
		cd_execution(command, s_environ, env_vars);
	else if (!ft_strcmp(command[0], "pwd"))
		pwd_execution(command, env_vars);
	else if (!ft_strcmp(command[0], "export"))
		export_execution(command, s_environ, env_vars);
	else if (!ft_strcmp(command[0], "env"))
		executing_env(command, s_environ);
	else if (!ft_strcmp(command[0], "unset"))
		unset_executing(command, s_environ);
	else if (!ft_strcmp(command[0], "exit"))
		exit_execution(tree, pid);
}

void	command_execution(t_tree *tree,
		t_env **environ, int flag, t_env_var **env_vars)
{
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
		if (!invalid_commands_checking(tree->data.argv[0]))
			return ;
		child_exerv(tree, environ, env_vars);
	}
}

void	redirection(t_tree *tree, t_env **environ, t_env_var **env_vars)
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
		last_command_arg(tree);
		command_execution(tree, environ, flag, env_vars);
	}
	else if (tree->type == 1)
	{
		flag = 1;
		pipe_line(tree, env_vars, environ);
	}
	redirection(tree, environ, env_vars);
}
