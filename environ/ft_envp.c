/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/04 19:40:07 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envp_clear(char **envp)
{
	char	**tmp;

	if (!envp)
		return ;
	tmp = envp;
	while (*tmp)
		free(*tmp++);
	free(envp);
}

char	**ft_envp(void)
{
	size_t	size;
	t_env	*env;
	char	**envp;
	char	**tmp;

	size = ft_envsize(ft_environ(NULL, 0));
	envp = (char **)malloc((size + 1) * sizeof(char *));
	if (!envp && ft_status(1))
		return (perror("malloc"), NULL);
	env = ft_environ(NULL, 0);
	tmp = envp;
	while (env)
	{
		*tmp = ft_strsjoin((char *[]){env->var, "=", env->val, NULL});
		if (!*tmp++ && ft_status(1))
			return (perror("malloc"), ft_envp_clear(envp), NULL);
		env = env->next;
	}
	*tmp = NULL;
	return (envp);
}
