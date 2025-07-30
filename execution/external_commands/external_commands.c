/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 00:19:25 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *variable(t_env *environ)
{
    char *tmp;
    char *join;

    tmp = custom_strjoin((environ->var),"=",1);
    if(!tmp)
        return(NULL);
    join = custom_strjoin(tmp,environ->val,1);
    return(join);
    
}
char **envp(t_env **environ)
{
    char **env;
    int count;
    t_env *tmp;
    char *var;
    
    (1 && (tmp = *environ), (count = 0));
    while(tmp)
    {
        count++;
        tmp =tmp->next;   
    }
    env=gc_malloc((count+1)*sizeof(char *),1);
    if(!env)
        return(NULL);
    tmp = *environ;
    count = 0;
    while(tmp)
    {
        var =variable(tmp);
        env[count]= var;
        tmp=tmp->next;
        count++;
    }
    env[count]= NULL;
    return(env);
}

int invalid_commands_checking(char *command,
    t_env **environ, t_env_var **env_vars)
{
    if(!ft_strlen(command)|| 
        !ft_strcmp(command,"..") || !ft_strcmp(command,"."))
    {
        ft_putstr_fd("Minishell: ", 2);
	    ft_putstr_fd(command , 2);
	    ft_putstr_fd(": command not found\n", 2);
        ft_status(127);
         return(0);
    }
    else if(there_is_slash(command,environ,env_vars))
    {
        if(!stat_the_command(command))
           return(0);
        return(1);
    }
    return(1);
}
int there_is_slash(char *command,t_env **environ, t_env_var **env_vars)
{
    int i;

    i = 0;
    while(command[i])
    {
        if(command[i] == '/')
            return(1);
        i++;
    }
    return(0);
}
static int stat_plus(char *command ,struct stat file_stat)
{
    if(S_ISREG(file_stat.st_mode))
    {
        if(file_stat.st_mode & S_IXUSR)
            return(1);
        else
        {
            print_msg("minishell: ", command, 
                ": Permission denied\n");
            ft_status(126);
        }
    }
    else if (S_ISDIR(file_stat.st_mode))
    {
        ft_status(126);
        print_msg("minishell: ", command, 
            ": is a Directory\n");
    }
    else
    {
        print_msg("minishell: ", command, 
            ": Not a regular file or directory\n");
        ft_status(126);
    }
    return(0);
} 
int stat_the_command(char *command)
{
    struct stat file_stat;
    
    if(stat(command, &file_stat) == -1)
    {   
        if(errno == ENOENT)
        {
            print_msg("minishell: ", command, 
                ": NO such file or directory\n");
            ft_status(127);
        }
        else if (errno == EACCES)
        {
            print_msg("minishell: ", command,
                 ": Permission denied\n");
            ft_status(126);
        }
        else
            perror("minishell : stat error");
    }
    else
        return(stat_plus(command ,file_stat));
    return(0);
}
void normal_execution(char **command,t_env **environ, t_env_var **env_vars)
{
    int flag;
    char **potential_paths;
    char **envp_;
    
    1 && (envp_= envp(environ), 
        (potential_paths = potential_path(environ,command[0])));
    if(!potential_paths)
    {
        ft_status(127);
        gc_malloc(0,0);
        exit(ft_status(-1));
    }
    flag = check_existans_and_permisisons(environ,
         command[0], env_vars);
    if(flag == -1)
        (1 && (gc_malloc(0,0)),(exit(ft_status(-1))));
    if(flag != -1 )
    {
        if(!execve(potential_paths[flag], command, envp_))
            (1 && (gc_malloc(0,0)),(exit(ft_status(-1))));
    }   
}

void external_commands_execution(char **command,
    t_env **environ, t_env_var **env_vars)
{
    char **envp_;

    envp_= envp(environ);
    if(command && command[0])
    {
        if(there_is_slash(command[0],environ, env_vars))
        {
            if(!execve(command[0], command, envp_))
            {
                gc_malloc(0,0);
                exit(ft_status(-1));
            }
        }
        else
            normal_execution(command,environ,env_vars);
    }
}

