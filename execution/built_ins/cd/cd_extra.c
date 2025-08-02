/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:24:42 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/02 15:11:03 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*telda_full_path(char *telda_path, t_env_var **env_vars)
{
	char	*telda_full_path;

	if (!telda_path)
	{
		telda_full_path = custom_strjoin((*env_vars)->home, telda_path, 1);
	}
	telda_full_path = custom_strjoin((*env_vars)->home, telda_path + 1, 1);
	if (!telda_full_path)
		return (NULL);
	else
		return (telda_full_path);
}


