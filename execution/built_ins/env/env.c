/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:49:08 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/22 23:31:45 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	printing_env(t_env *current)
{
	printf("%s", current->var);
	printf("=");
	printf("%s", current->val);
	printf("\n");
}

void	executing_env(char **command, t_env **environ)
{
	t_env	*current;

	current = *environ;
	if (current == NULL)
		return ;
	if (command[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		ft_status(127);
		return ;
	}
	while (current)
	{
		if (current->val)
			printing_env(current);
		current = current->next;
	}
	ft_status(0);
}
