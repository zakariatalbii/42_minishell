/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/11 01:26:08 by wnid-hsa         ###   ########.fr       */
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

// static int	ft_pwdenv(t_env **env)
// {
// 	struct stat	s;
// 	t_env		*new;
// 	char		*opwd;
// 	char		*getcwd_;

// 	*env = NULL;
// 	getcwd_ = getcwd(NULL, 0);
// 	if (!getcwd_)
// 		return (perror("getcwd"), -1);
// 	new = ft_envnew(custom_strdup("PWD",1),getcwd(NULL, 0) );
// 	if (!new && ft_status(1))
// 		return (perror("malloc"),free(getcwd_), -1);
// 	ft_envadd(env, new);
// 	opwd = getenv("OLDPWD");
// 	if (opwd && !stat(opwd, &s) && S_ISDIR(s.st_mode))
// 	{
// 		new = ft_envnew(custom_strdup("OLDPWD",1), custom_strdup(opwd,1));
// 		if (!new && ft_status(1))
// 			return (perror("malloc"), -1);
// 		ft_envadd(env, new);
// 	}
// 	return (free(getcwd_),0);
// }
static int ft_pwdenv(t_env **env)
{
    struct stat s;
    t_env *new;
    char *opwd;
    char *getcwd_;
    
    *env = NULL;
    getcwd_ = getcwd(NULL, 0);
    if (!getcwd_)
        return (perror("getcwd"), -1);
    new = ft_envnew(custom_strdup("PWD", 1), custom_strdup(getcwd_, 1));
    if (!new && ft_status(1))
    {
        free(getcwd_); 
        return (perror("malloc"), -1);
    }
    ft_envadd(env, new);
    opwd = getenv("OLDPWD");
    if (opwd && !stat(opwd, &s) && S_ISDIR(s.st_mode))
    {
        new = ft_envnew(custom_strdup("OLDPWD", 1), custom_strdup(opwd, 1));
        if (!new && ft_status(1))
        {
            free(getcwd_);
            return (perror("malloc"), -1);
        }
        ft_envadd(env, new);
    }
    free(getcwd_);
    return (0);
}

static int	ft_shlvlenv(t_env **env)
{
	t_env	*new;
	char	*shlvl;
	int		shl;
	char	*itoa_value;

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
	itoa_value = ft_itoa(shl);
	new = ft_envnew(custom_strdup("SHLVL",1),custom_strdup(itoa_value,1));
	if (!new && ft_status(1))
		return (perror("malloc") ,free(itoa_value), -1);
	ft_envadd(env, new);
	return (free(itoa_value),0);
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
			new = ft_envnew(custom_strndup(environ[v], len,1),
					custom_strdup(&environ[v][len + 1],1));
			if (!new && ft_status(1))
				return (perror("malloc"), ft_envclear(&env), NULL);
			ft_envadd(&env, new);
		}
		v++;
	}
	return (env);
}
