/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:17:13 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/07 17:49:37 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_handling(int return_value, char *failed_function, char *path)
{
	if (return_value == -1)
	{
		if (!ft_strcmp(failed_function, "close"))
			perror("close failed");
		if (!ft_strcmp(failed_function, "dup2"))
			perror("dup2 failed");
		if (!ft_strcmp(failed_function, "fork"))
			perror("fork failed");
		if (!ft_strcmp(failed_function, "dup"))
			perror("dup failed");
		if (!ft_strcmp(failed_function, "open"))
		{
			if (errno == ENOENT)
			{
				print_msg("minishell: ", path, ": No such file or directory\n");
				ft_status(1);
			}
			else if (errno == EACCES)
			{
				print_msg("minishell: ", path, ": Permission denied\n");
				ft_status(1);
			}
		}
	}
}

void	status_handling_chid(int status_2)
{
	int	sig;

	ft_signals(1);
	if (WIFSIGNALED(status_2))
	{
		sig = WTERMSIG(status_2);
		if (sig == SIGINT)
			(1 && (ft_status(130)), (ft_putchar_fd('\n', 1)));
		else if (sig == SIGQUIT)
		{
			ft_status(131);
			printf("Quit (core dumped)\n");
		}
	}
	else if (WIFEXITED(status_2))
		ft_status(WEXITSTATUS(status_2));
	else
		ft_status(1);
}

void	status_handling(int status_1)
{
	int	sig;

	ft_signals(1);
	if (WIFSIGNALED(status_1))
	{
		sig = WTERMSIG(status_1);
		if (sig == SIGINT)
		{
			ft_status(130);
			ft_putchar_fd('\n', 1);
		}
		else if (sig == SIGQUIT)
		{
			ft_status(131);
			printf("Quit (core dumped)\n");
		}
	}
	else if (WIFEXITED(status_1))
		ft_status(WEXITSTATUS(status_1));
	else
		ft_status(1);
}

void	change_lst_arg_(char *last_arg)
{
	char	*lst_arg;

	if (!ft_strcmp(last_arg, "env"))
		lst_arg = "/usr/bin/env";
	else if (!ft_strcmp(last_arg, "export"))
		return ;
	else
		lst_arg = custom_strdup(last_arg, 1);
	ft_setenv("_", lst_arg, 0);
}

void	last_command_arg(t_tree *tree)
{
	char	**args;
	char	*last_arg;
	int		i;

	i = 0;
	args = tree->data.argv;
	if (!args)
		return ;
	while (args && args[i])
	{
		i++;
	}
	last_arg = args[i - 1];
	change_lst_arg_(last_arg);
}
