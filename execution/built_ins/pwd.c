/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:06 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/22 23:39:45 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_pwd(char	**command)
{
	if (!ft_strcmp(command[1], "-p")
		|| !ft_strcmp(command[1], "--p" ) || !ft_strcmp(command[1], "---p"))
		return (0);
	else
		return (1);
}

char	*get_value(char *var, t_env *environ)
{
	while (environ)
	{
		if (!ft_strcmp(environ->var, var))
			return (environ->val);
		environ = environ->next;
	}
	return (NULL);
}

void	pwd_execution(char **command, t_env_var **env_vars)
{
	if (command[1] && !is_valid_pwd(command))
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putchar_fd(command[1][0], 2);
		ft_putchar_fd(command[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_status(2);
		return ;
	}
	else
	{
		printf("%s\n", (*env_vars)->pwd);
		ft_status(0);
	}
}
