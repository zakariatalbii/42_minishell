/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:49:22 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/01 23:52:54 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	cd_errno_handling(int ernum, char *path)
{
	if (ernum == ENOTDIR)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (ernum == EACCES)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
	}
	else if (ernum == ENOENT)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	print_msg(char *text1, char *text2, char *text3)
{
	ft_putstr_fd(text1, 2);
	ft_putstr_fd(text2, 2);
	ft_putstr_fd (text3, 2);
}

int	is_it_set(t_env **environ, char *var)
{
	t_env	*current;

	current = (*environ);
	while (current)
	{
		if (!ft_strcmp(current->var, var))
		{
			if (!(current->val)
				|| (!ft_strcmp(var, "OLDPWD") && !ft_strcmp(current->val, "")))
			{
				print_msg("minishell: cd: ", var, " not set\n");
				return (0);
			}
			else if (!ft_strcmp(current->val, ""))
			{
				print_msg("minishell: cd: ", var, " is empty\n");
				return (0);
			}
			return (1);
			break ;
		}
		current = current->next;
	}
	print_msg("minishell: cd: ", var, " not set\n");
	return (0);
}
