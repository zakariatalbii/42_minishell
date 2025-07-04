/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/04 19:40:23 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *var)
{
	t_env	*env;

	env = ft_environ(NULL, 0);
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

char	*ft_getlenv(char *var, size_t len)
{
	t_env	*env;

	env = ft_environ(NULL, 0);
	while (env)
	{
		if (ft_strlen(env->var) == len && !ft_strncmp(env->var, var, len))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
