/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:49:08 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/23 03:38:54 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void   printing_env(t_env *current)
{
    printf("%s", current->var);
    printf("=");
    printf("%s", current->val);
    printf("\n");  
} 

void executing_env(t_env **environ, t_env_var **env_vars)
{
    t_env *current;

    current = *environ;
    if (current == NULL)
        return;
    if(ft_unset_flag(0)== 1)
    {
        ft_putstr_fd("minishell: env: No such file or directory\n",2);
        ft_status(127);
        return;
    }
    while(current)
    {
        if(current->val)
            printing_env(current);
        current= current->next;
    }
    ft_status(0);
}
