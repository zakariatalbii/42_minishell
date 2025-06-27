/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/27 10:59:07 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int is_a_directory(char *command, t_env_var **env_vars)
{
    if(command[ft_strlen(command)-1] == '/')
    {
        if(!chdir(command))
        {
            printf("bash: %s: Is a directory\n", command);
            *((*env_vars)->status)=1;
            if(chdir((*env_vars)->pwd))
                printf("chdir error\n");
            return(1);
        }
        return(0);
    }
    return(0);
}
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
static int full_path(char *command)
{
    if(command[0] == '/')
        return(1);
    else if(!ft_strncmp(command,"./", 2))
        return(2);
    else if(command[ft_strlen(command)-1] == '/')
        return(4);
    return(0);
    
}
// static char *shell_level(t_environ **environ)
// {
//     while(environ && *environ)
//     {
//         if(!ft_strcmp((*environ)->var,"SHLVL"))
            
//     }
// }

static char *current_directory(char *command, t_env_var **env_vars)
{
    char *current_directory;
    char *tmp;

    char **split_it;
    split_it = custom_split(command,'/', 0);
    if(!split_it || !split_it[1])
        return(NULL);
    tmp= custom_strjoin((*env_vars)->pwd, "/",0);
    if(!tmp)
        return(NULL);
    current_directory= custom_strjoin(tmp, split_it[1],0);
    return(current_directory);
}
void external_commands_execution(char **command,t_environ **environ, t_env_var **env_vars)
{
    int flag;
    char **potential_paths;
    char *full_path_;
    static char *mkdir_path;
    
    (void)environ;
    if(full_path(command[0]))
    {
        if(full_path(command[0])==2)
        {
            full_path_= current_directory(command[0], env_vars);
            {
                export_execution()
            }
            if(!full_path_)
                return;
        }
        else if(full_path(command[0]) == 1)
            full_path_  = command[0];
        else if(full_path(command[0]) == 4)
        {
            if(is_a_directory(command[0], env_vars)==1)
                return;
        }
        flag = check_full_path(full_path_, env_vars);
        if(flag == -1)
        {
            gc_malloc(0,0);
            exit(*((*env_vars)->status));
        }
        else if(flag == 1)
        {
            if(!execve(full_path_, command, NULL))
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
            // execve(potential_paths[flag], command, NULL);
            if(!execve(potential_paths[flag], command, NULL))
            {
                gc_malloc(0,0);
                exit(*((*env_vars)->status));
            }
        }
    }
}
// void external_commands_execution(char **command,t_environ **environ, t_env_var **env_vars)
// {
//     int flag;
//     char **potential_paths;
    
//     (void)environ;
//     potential_paths = potential_path(environ,command[0],env_vars);
//     if(!potential_paths)
//     {
//         printf("bash: No such file or directory\n");
//         *((*env_vars)->status)=127;
//         exit(*((*env_vars)->status));
//     }
//     flag = check_existans_and_permisisons(environ, command[0], env_vars);
//     if(flag == -1)
//         exit(*((*env_vars)->status));
//     if(flag != -1 )
//     {
//         execve(potential_paths[flag], command, NULL);
//     }
//     else
//     {
//         printf("path_error\n");
//     }
// }
