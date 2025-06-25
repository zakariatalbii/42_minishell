/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/25 21:14:59 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int  check_full_path(char *full_path, t_env_var **env_vars)
{
	
	if(access(full_path, F_OK) == 0)
	{
		if(access(full_path, X_OK ) == 0)
			return(1);
		else
		{
			printf("permission denied");
			*((*env_vars)->status) = 126;
			return(-1);
		}
	}
	*((*env_vars)->status) = 127;
	printf("bash: %s: command not found\n", full_path);
	return(-1);
}   
static int is_it_full_path(char *command)
{
    int i;

    i = 0;
    if(command[0] == '/')
        return(1);
    else
        return(0);
    
}
void external_commands_execution(char **command,t_environ **environ, t_env_var **env_vars)
{
    int flag;
    char **potential_paths;
    
    (void)environ;
    if(is_it_full_path(command[0]))
    {
        flag =check_full_path(command[0], env_vars);
        if(flag == -1)
        {
            gc_malloc(0,0);
            exit(*((*env_vars)->status));
        }
        if(flag != -1 )
        {
            execve(command[0],command, NULL);
            if(!execve(command[0], command, NULL))
            {
                gc_malloc(0,0);
                exit(*((*env_vars)->status));
            }
        }
    }
    else
    {
        potential_paths = potential_path(environ,command[0],env_vars);
        if(!potential_paths)
        {
            printf("bash: No such file or directory\n");
            *((*env_vars)->status)=127;
            gc_malloc(0,0);
            exit(*((*env_vars)->status));
        }
        flag = check_existans_and_permisisons(environ, command[0], env_vars);
        if(flag == -1)
        {
            gc_malloc(0,0);
            exit(*((*env_vars)->status));
        }
        if(flag != -1 )
        {
            execve(potential_paths[flag], command, NULL);
            if(!execve(potential_paths[flag], command, NULL))
            {
                gc_malloc(0,0);
                exit(*((*env_vars)->status));
            }
        }
    }
}
