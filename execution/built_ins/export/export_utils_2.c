/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:00:34 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/07 17:42:08 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_unset_flag(int flag)
{
	static int	flag_;

	if (flag == 0)
		return (flag_);
	else
	{
		flag_ = flag;
		return (flag_);
	}
}

int	unset_pwd_flag(int set_flag)
{
	static int	flag;

	flag = 0;
	if (set_flag == 1)
		flag = 1;
	else if (set_flag == -1)
		flag = 0;
	return (flag);
}

void	print_chr_str(char *text1, char c1, char c2, char *text2)
{
	ft_putstr_fd(text1, 2);
	write(2, &c1, 1);
	write(2, &c2, 1);
	ft_putstr_fd(text2, 2);
}

int	var_name_error(char *arg, int flag)
{
	int	i;
	int	var_name_end_;

	i = 0;
	while (arg[i])
	{
		var_name_end_ = (var_name_end(arg));
		if (!valid_var_name(arg, var_name_end_))
		{
			if (arg[0] == '-' && flag == 1)
			{
				print_chr_str("minishell: export ",
					arg[0], arg[1], ": invalid option\n");
				ft_status(2);
				return (1);
			}
			print_msg("minishell: export `",
				arg, "': not a valid identifier\n");
			ft_status(1);
			return (1);
		}
		i++;
	}
	return (0);
}
