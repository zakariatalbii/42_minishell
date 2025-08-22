/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:05:58 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/07 17:42:43 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	replace_node(t_environ **new, t_env_var **env_vars)
{
	if (!new)
		return ;
	else
	{
		if (!(*new)->operator)
		{
			if (!((*new)->value))
			{
				if (ft_getenv((*new)->var))
					return ;
				else
					ft_setenv((*new)->var, (*new)->value, 0);
			}
		}
		else if (!ft_strcmp((*new)->operator, "+="))
			ft_setenv((*new)->var, (*new)->value, 1);
		else if (!ft_strcmp((*new)->operator, "="))
			ft_setenv((*new)->var, (*new)->value, 0);
		if (!ft_strcmp((*new)->var, "PWD") && !(*new)->value)
			ft_setenv((*new)->var, (*env_vars)->pwd, 0);
		if (!ft_strcmp((*new)->var, "OLDPWD") && !(*new)->value)
			ft_setenv((*new)->var, (*env_vars)->oldpwd, 0);
	}
}

void	handling_new_changes(t_environ **new, t_env_var **env_vars)
{
	if (!*new)
		return ;
	if (!((*new)->value))
		return ;
	else if (!ft_strcmp((*new)->operator, "+=")
		&& !ft_strcmp((*new)->value, ""))
		return ;
	replace_node(new, env_vars);
}

static int	input_struct_handling(char *arg, int flag)
{
	if (!arg)
		return (1);
	if (!ft_strlen(arg))
	{
		print_msg("minishell: export `", arg, "': not a valid identifier\n");
		ft_status(1);
		return (1);
	}
	return (var_name_error(arg, flag));
}

static void	command_handling(int *flag, char **command, t_env_var **env_vars)
{
	t_environ	*new;
	int			i;

	i = 1 ;
	while (command && command[i])
	{
		if (valid_position_export(command[i]))
		{
			if (input_struct_handling(command[i], i))
			{
				*flag = 1;
				i++;
				continue ;
			}
			new = ft_lstnew_environ(command[i]);
			export_flags_apdate(new, env_vars);
		}
		else
		{
			(ft_status(1), *flag = 1);
			print_msg("minishell: export `",
				command[i], "': not a valid identifier\n");
		}
		i++;
	}
}

void	make_export_struct(char **command, t_env_var **env_vars)
{
	int	flag;

	flag = 0;
	if (command)
	{
		command_handling(&flag, command, env_vars);
		if (flag == 0)
			ft_status(0);
	}
}
