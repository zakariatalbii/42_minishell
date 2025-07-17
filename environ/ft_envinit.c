/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/17 02:34:05 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_varlen(char *s)
{
	size_t	v;

	v = 0;
	while (s[v] && s[v] != '=')
		v++;
	return (v);
}

static int	ft_pwdenv(t_env **env)
{
	t_env		*new;

	*env = NULL;
	new = ft_envnew(ft_strdup("OLDPWD"), NULL, 1, 0);
	if (!new && ft_status(1))
		return (perror("malloc"), ft_envclear(env), -1);
	ft_envadd(env, new);
	new = ft_envnew(ft_strdup("PWD"), getcwd(NULL, 0), 1, 1);
	if (!new && ft_status(1))
		return (perror("malloc"), ft_envclear(env), -1);
	ft_envadd(env, new);
	return (0);
}

static int	ft_shlvlenv(t_env **env)
{
	t_env	*new;
	char	*shlvl;
	int		shl;

	shl = 1;
	shlvl = getenv("SHLVL");
	if (shlvl)
		shl += ft_atoi(shlvl);
	if (shl < 0)
		shl = 0;
	else if (shl > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(shl, 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		shl = 1;
	}
	new = ft_envnew(ft_strdup("SHLVL"), ft_itoa(shl), 1, 1);
	if (!new && ft_status(1))
		return (perror("malloc"), ft_envclear(env), -1);
	ft_envadd(env, new);
	return (0);
}

t_env	*ft_envinit(void)
{
	t_env	*env;
	t_env	*new;
	size_t	len;
	size_t	v;

	if (ft_pwdenv(&env) || ft_shlvlenv(&env))
		return (NULL);
	v = 0;
	while (environ[v])
	{
		len = ft_varlen(environ[v]);
		if (ft_strncmp(environ[v], "PWD=", 4)
			&& ft_strncmp(environ[v], "OLDPWD=", 7)
			&& ft_strncmp(environ[v], "SHLVL=", 6))
		{
			new = ft_envnew(ft_strndup(environ[v], len),
					ft_strdup(&environ[v][len + 1]), 1, 1);
			if (!new && ft_status(1))
				return (perror("malloc"), ft_envclear(&env), NULL);
			ft_envadd(&env, new);
		}
		v++;
	}
	return (env);
}
