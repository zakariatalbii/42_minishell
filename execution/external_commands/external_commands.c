/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/30 13:16:30 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void external_commands_execution(char **command,t_environ **environ)
{
    int flag;
    char **potential_paths;
    
    (void)environ;
    potential_paths =potential_path(command[0]);
    flag = check_existans_and_permisisons(command[0]);
    
    if(flag != -1 || potential_paths!=NULL)
    {
        execve(potential_paths[flag], command, NULL);
    }
    else
    {
        printf("path_error\n");
    }
}