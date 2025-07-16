/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/04 19:39:15 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_envnew(char *var, char *val)
{
	t_env	*node;

	if (var && val)
		node = (t_env *)malloc(sizeof(t_env));
	if (!var || !val || !node)
		return (free(var), free(val), NULL);
	node->var = var;
	node->val = val;
	node->next = NULL;
	return (node);
}

void	ft_envadd(t_env **env, t_env *new)
{
	t_env	*node;

	if (!env || !new)
		return ;
	if (!*env)
		*env = new;
	else
	{
		node = *env;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

int	ft_envsize(t_env *env)
{
	int	v;

	v = 0;
	while (env)
	{
		env = env->next;
		v++;
	}
	return (v);
}

void	ft_envclear(t_env **env)
{
	t_env	*node;

	if (env == NULL)
		return ;
	while (*env != NULL)
	{
		node = *env;
		*env = node->next;
		free(node->var);
		free(node->val);
		free(node);
	}
}
