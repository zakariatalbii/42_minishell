/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/23 02:40:54 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


static int is_a_directory(char *command,t_env *environ, t_env_var **env_vars)
{
    if(command[ft_strlen(command)-1] == '/')
    {
        if(!chdir(command))
        {
            ft_putstr_fd("bash: ",2);
            ft_putstr_fd(command,2);
            ft_putstr_fd(": Is a directory\n",2);
            ft_status(126);
            if(chdir(get_value("PWD", environ)))
                ft_putstr_fd("chdir error\n",2);
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
        {
			return(1);
        }
		else
		{
			ft_putstr_fd("permission denied",2);
			ft_status(126);
			return(-1);
		}
	}
	ft_status(127);
	ft_putstr_fd("Minishell: ",2);
    ft_putstr_fd(full_path,2);
    ft_putstr_fd(": No such file or directory\n",2);
	return(-1);
} 

static int full_path(char *command, t_env **environ, t_env_var **env_vars)
{   
    if(!ft_strlen(command))
    {
        ft_putstr_fd("Minishell: ", 2);
	    ft_putstr_fd(command , 2);
	    ft_putstr_fd(": command not found\n", 2);
        *((*env_vars)->status)=127;
        return(-2);
    }
    if(command[0] == '/')
    {
        if(!chdir(command))
        {
            ft_putstr_fd("Minishell: ",2);
            ft_putstr_fd(command,2);
            ft_putstr_fd(": Is a directory\n",2);
            *((*env_vars)->status)=126;
            if(chdir(get_value("PWD", *environ)))
                perror("chdir error\n");
            return(-2);
        }
        return(1);
    }     
    else if(!ft_strncmp(command,"./", 2))
    {
        if(!chdir(command))
        {
            ft_putstr_fd("bash: Is a directory\n",2);
            *((*env_vars)->status)=1;
            if(chdir(get_value("PWD", *environ)))
                perror("chdir error\n");
        }
        return(2);
    }   
    else if(command[ft_strlen(command)-1] == '/')
        return(4);
    else
        return(0);
}

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
    
    tmp = *environ;
    count = 0;
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
static char *current_directory(char *command, t_env *environ)
{
    char *current_directory;
    char *tmp;

    char **split_it;
    split_it = custom_split(command,'/', 0);
    if(!split_it || !split_it[1])
        return(NULL);
    tmp= custom_strjoin(get_value("PWD",environ), "/",0);
    if(!tmp)
        return(NULL);
    current_directory= custom_strjoin(tmp, split_it[1],0);
    return(current_directory);
}

static int there_is_slash(char *command,t_env **environ, t_env_var **env_vars)
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
int stat_the_command(char *command)
{
    struct stat file_stat;
    
    if(stat(command, &file_stat) == -1)
    {   
        if(errno == ENOENT)
        {
            ft_putstr_fd("Minishell ",2);
            ft_putstr_fd(command, 2);
            ft_putstr_fd(": NO such file or directory\n",2);
        }
        else if (errno == EACCES)
        {
            ft_putstr_fd("Minishell ",2);
            ft_putstr_fd(command, 2);
            ft_putstr_fd(": Permission denied\n",2);
        }
        else
            perror("Minishell : stat error");
        return(0);
    }
    else
    {
        if(S_ISREG(file_stat.st_mode))
        {
            if(file_stat.st_mode & S_IXUSR)
                return(1);
            else
            {
                ft_putstr_fd("Minishell ",2);
                ft_putstr_fd(command, 2);
                ft_putstr_fd(": Permission denied\n",2);
            }
        }
        else if (S_ISDIR(file_stat.st_mode))
        {
            ft_status(126);
            ft_putstr_fd("Minishell ",2);
            ft_putstr_fd(command, 2);
            ft_putstr_fd(": is a Directory\n",2);
        }
        else
        {
            ft_putstr_fd("Minishell ",2);
            ft_putstr_fd(command, 2);
            ft_putstr_fd(": Not a regular file or directory\n",2);
        }
        return(0);
    }
}
void normal_execution(char **command,t_env **environ, t_env_var **env_vars)
{
    int flag;
    char **potential_paths;
    char **envp_;
    
    1 && (envp_= envp(environ), (potential_paths = potential_path(environ,command[0])));
    if(!potential_paths)
    {
        ft_status(127);
        gc_malloc(0,0);
        exit(ft_status(-1));
    }
    flag = check_existans_and_permisisons(environ, command[0], env_vars);
    if(flag == -1)
    {
        gc_malloc(0,0);
        exit(ft_status(-1));
    }
    if(flag != -1 )
    {
        if(!execve(potential_paths[flag], command, envp_))
        {
            gc_malloc(0,0);
            exit(ft_status(-1));
        }
    }   
}

void external_commands_execution(char **command,t_env **environ, t_env_var **env_vars)
{
    char **envp_;

    envp_= envp(environ);
    if(command && command[0])
    {
        if(!ft_strlen(command[0]))
        {
            ft_putstr_fd("Minishell: ", 2);
	        ft_putstr_fd(command[0] , 2);
	        ft_putstr_fd(": command not found\n", 2);
            ft_status(127);
            return;
        }
        if(there_is_slash(command[0],environ,env_vars))
        {
            if(!stat_the_command(command[0]))
                return;
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

