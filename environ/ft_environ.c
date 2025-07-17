/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/17 01:03:57 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_environ_clear(void)
{
	t_env	*env;

	env = ft_environ(NULL, NULL, 0);
	ft_envclear(&env);
	ft_environ(NULL, NULL, 1);
}

t_env	*ft_environ(t_env ***penv, t_env *env, int flag)
{
	static t_env	*envs;

	if (flag)
		envs = env;
	if (penv)
		*penv = &envs;
	return (envs);
}
