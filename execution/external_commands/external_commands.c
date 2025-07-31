/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/31 11:29:51 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*variable(t_env *environ)
{
	char	*tmp;
	char	*join;

	tmp = custom_strjoin((environ->var), "=", 1);
	if (!tmp)
		return (NULL);
	join = custom_strjoin(tmp, environ->val, 1);
	return (join);
}

char	**envp(t_env **environ)
{
	char	**env;
	int		count;
	t_env	*tmp;
	char	*var;

	(1 && (tmp = *environ), (count = 0));
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env = gc_malloc((count + 1) * sizeof(char *), 1);
	if (!env)
		return (NULL);
	tmp = *environ;
	count = 0;
	while (tmp)
	{
		var = variable(tmp);
		env[count] = var;
		tmp = tmp->next;
		count++;
	}
	env[count] = NULL;
	return (env);
}

void	normal_execution(char **command, t_env **environ, t_env_var **env_vars)
{
	int		flag;
	char	**potential_paths;
	char	**envp_;

	1 && (envp_ = envp(environ),
		(potential_paths = potential_path(environ, command[0])));
	if (!potential_paths)
	{
		ft_status(127);
		gc_malloc(0, 0);
		close_fds();
		exit(ft_status(-1));
	}
	flag = check_existans_and_permisisons(environ,
			command[0], env_vars);
	if (flag == -1)
		(1 && (gc_malloc(0, 0)), close_fds(),(exit(ft_status(-1))));
	if (flag != -1)
	{
		if (!execve(potential_paths[flag], command, envp_))
			(1 && (gc_malloc(0, 0)), close_fds(),(exit(ft_status(-1))));
	}
}

void	external_commands_execution(char **command,
	t_env **environ, t_env_var **env_vars)
{
	char	**envp_;

	envp_ = envp(environ);
	if (command && command[0])
	{
		if (there_is_slash(command[0], environ, env_vars))
		{
			if (!execve(command[0], command, envp_))
			{
				gc_malloc(0, 0);
				close_fds();
				exit(ft_status(-1));
			}
		}
		else
			normal_execution(command, environ, env_vars);
	}
}
