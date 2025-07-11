/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:05:07 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/10 22:21:42 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_setnew(char *var, char *val)
{
	t_env	*env;
	t_env	*new;

	env = ft_environ(NULL, 0);
	new = ft_envnew(var, val);
	if (!new && ft_status(1))
		return (perror("malloc"), -1);
	ft_envadd(&env, new);
	return (0);
}

int	ft_setenv(char *var, char *val, int flag)
{
	t_env	*env;
	char	*str;

	env = ft_environ(NULL, 0);
	while (env)
	{
		if (!flag && !ft_strcmp(env->var, var))
		{
			str = custom_strdup(val,1);
			if (!str && ft_status(1))
				return (perror("malloc"), -1);
			return (env->val = str, 0);
		}
		else if (flag && !ft_strcmp(env->var, var))
		{
			str = custom_strjoin(env->val, val,1);
			if (!str && ft_status(1))
				return (perror("malloc"), -1);
			return (env->val = str, 0);
		}
		env = env->next;
	}
	return (ft_setnew(custom_strdup(var,1), custom_strdup(val,1)));
}

int   ft_unset_flag(int flag)
{
	static int flag_;

	if(flag == 0)
		return(flag_);
	else
	{
		flag_ = flag;
		return(flag_);
	}
}

void	ft_unsetenv(char *var)
{
	t_env	*env;
	t_env	*tmp;

	// printf("%s\n", var);
	env = ft_environ(NULL, 0);
	if (env && !ft_strcmp(env->var, var))
	{
		ft_environ(env->next, 1);
		// free(env->var);
		// free(env->val);
		// free(env);
		return ;
	}
	while (env)
	{
		tmp = env->next;
		if (tmp && !ft_strcmp(tmp->var, var))
		{
			if(!ft_strcmp(var ,"PATH"))
				(void)ft_unset_flag(1);
			env->next = tmp->next;
			// free(tmp->var);
			// free(tmp->val);
			// free(tmp);
			return ;
		}
		env = env->next;
	}
}
