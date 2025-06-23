/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 06:30:25 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void external_commands_execution(char **command,t_environ **environ, t_env_var **env_vars)
{
    int flag;
    char **potential_paths;
    
    (void)environ;
    potential_paths = potential_path(environ,command[0],env_vars);
    if(!potential_paths)
    {
        printf("bash: No such file or directory\n");
        *((*env_vars)->status)=127;
        exit(*((*env_vars)->status));
        
    }
    flag = check_existans_and_permisisons(environ, command[0], env_vars);
    if(flag == -1)
        exit(*((*env_vars)->status));
    if(flag != -1 )
    {
        execve(potential_paths[flag], command, NULL);
    }
    else
    {
        printf("path_error\n");
    }
}
