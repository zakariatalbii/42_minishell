/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:08:35 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/04 05:18:20 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	invalid_commands_checking(char *command)
{
	if (!ft_strlen(command)
		|| !ft_strcmp(command, "..") || !ft_strcmp(command, "."))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_status(127);
		return (0);
	}
	else if (there_is_slash(command))
	{
		if (!stat_the_command(command))
			return (0);
		return (1);
	}
	return (1);
}

int	there_is_slash(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	stat_plus(char *command, struct stat file_stat)
{
	if (S_ISREG(file_stat.st_mode))
	{
		if (file_stat.st_mode & S_IXUSR)
			return (1);
		else
		{
			print_msg("minishell: ", command,
				": Permission denied\n");
			ft_status(126);
		}
	}
	else if (S_ISDIR(file_stat.st_mode))
	{
		ft_status(126);
		print_msg("minishell: ", command,
			": is a Directory\n");
	}
	else
	{
		print_msg("minishell: ", command,
			": Not a regular file or directory\n");
		ft_status(126);
	}
	return (0);
}

int	stat_the_command(char *command)
{
	struct stat	file_stat;

	if (stat(command, &file_stat) == -1)
	{
		if (errno == ENOENT)
		{
			print_msg("minishell: ", command,
				": NO such file or directory\n");
			ft_status(127);
		}
		else if (errno == EACCES)
		{
			print_msg("minishell: ", command,
				": Permission denied\n");
			ft_status(126);
		}
		else
			perror("minishell : stat error");
	}
	else
		return (stat_plus(command, file_stat));
	return (0);
}
