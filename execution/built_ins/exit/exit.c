/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:48:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 04:06:16 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	parssing(t_tree *tree, t_env_var **env_vars, int pid)
{
	int	i;
	int	flag;

	(1 && (i = 1), (flag = 0));
	if (tree->data.argv[1][0] != '-' &&
		tree->data.argv[1][0] != '+' && !ft_is_a_numb(tree->data.argv[1][0]))
		flag = 1;
	if ((ft_strlen(tree->data.argv[1]) > 1
			&&!ft_is_a_numb(tree->data.argv[1][1])))
		flag = 1;
	if (ft_lg__atoi(tree->data.argv[1]) == -111)
		flag = 1;
	if (flag == 1)
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(tree->data.argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_status(255);
		exiting(tree, env_vars, 0, pid);
	}
}

static void	exit_argument_parssing(t_tree *tree, t_env_var **env_vars, int pid)
{
	char	**command ;

	command = tree->data.argv;
	if (command[0] && command[1])
	{
		if (pid == 1)
			printf("exit\n");
		parssing(tree, env_vars, pid);
		if (command[2])
		{
			ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
			ft_status(1);
			return ;
		}
		real_exit_status(tree, env_vars, pid);
	}
}

void	exit_execution(t_tree *tree, t_env_var **env_vars, int pid)
{
	char	**command;

	command = tree->data.argv;
	exit_argument_parssing(tree, env_vars, pid);
	if (command[0] && command[1] == NULL)
	{
		if (pid == 1)
			printf("exit\n");
		exiting(tree, env_vars, 1, pid);
	}
}
