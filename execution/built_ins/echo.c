/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:44 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 05:22:09 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	identify_the_arg(char **str, int *i)
{
	int	j ;

	j = 0;
	while (str[*i])
	{
		if (str[*i][0] == '-')
		{
			if (!ft_strcmp(str[*i], "-"))
				return (0);
			j = 1;
			while (str[*i][j])
			{
				if (str[*i][j] != 'n')
					return (0);
				j++;
			}
		}
		else
			return (0);
		(*i)++;
	}
	return (1);
}

static void	echo_new_line(char **command, int *new_line, int *i)
{
	if (!identify_the_arg((command), i))
	{
		if (*i != 1)
			*new_line = 1;
	}
	else
	{
		if (!command[1])
			*new_line = 0;
		else
			*new_line = 1;
	}
}

void	echo_execution(char **command, t_env_var **env_vars)
{
	int	i;
	int	new_line;

	new_line = 0;
	i = 1;
	echo_new_line(command, &new_line, &i);
	while ((command)[i])
	{
		ft_putstr_fd((command)[i], 1);
		if ((command)[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", 1);
	ft_status(0);
}
