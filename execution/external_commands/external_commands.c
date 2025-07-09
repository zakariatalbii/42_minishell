/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:54:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/28 16:06:49 by wnid-hsa         ###   ########.fr       */
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
            *((*env_vars)->status)=126;
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
			*((*env_vars)->status) = 126;
			return(-1);
		}
	}
	*((*env_vars)->status) = 127;
	ft_putstr_fd("bash: command not found\n",2);
	return(-1);
} 
static int get_shlvl_value(t_env *environ)
{
    int value;
    
    while(environ)
    {
        if(!ft_strcmp(environ->var,"SHLVL"))
            value = ft_atoi(environ->val);
        environ=environ->next;
    }
    return(1);
}  
static int full_path(char *command, t_env **environ, t_env_var **env_vars)
{
    char *shlvl;
    int  new_shlvl;
    t_env *new;
    char *join;
    
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
static char *current_directory(char *command, t_env *environ, t_env_var **env_vars)
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
// int path_type(char *command, t_env **environ, t_env_var **env_vars)
// {

// }
void external_commands_execution(char **command,t_env **environ, t_env_var **env_vars)
{
    int flag;
    char **potential_paths;
    char *full_path_;
    char **envp_;
    static int *flag_;
    int path_type;
    // int  shlv_flag;
    // char *shlvl;
    // int  new_shlvl;
    // t_env *new;
    char *join;

    envp_= envp(environ);
    if(command && command[0])
    {
        path_type = full_path(command[0], environ,env_vars);
        if(path_type != 0)
        {
            if(path_type == 2)
            {
                full_path_= current_directory(command[0] ,*environ, env_vars);
                if(!full_path_)
                    return;
                flag = check_full_path(full_path_, env_vars);
            }
            else if(path_type == 1)
            {
                full_path_  = command[0];
                flag = check_full_path(full_path_, env_vars);
            }
            else if(path_type == 4)
            {
                if(is_a_directory(command[0], *environ, env_vars) == 1)
                    flag = -1;
                else
                    flag = check_full_path(full_path_, env_vars);
            }
            else if(path_type <0)
                flag = -1;
            if(flag == -1)
            {
                gc_malloc(0,0);
                exit(*((*env_vars)->status));
            }
            else if(flag == 1)
            {
                if(!execve(full_path_, command, envp_))
                {
                    gc_malloc(0,0);
                    exit(*((*env_vars)->status));
                }
            }
        }
        else
        {
                
            potential_paths = potential_path(environ,command[0],env_vars, flag_);
            if(!potential_paths)
            {
                *((*env_vars)->status)=127;
                // ft_status(127);
                gc_malloc(0,0);
                exit(*((*env_vars)->status));
            }
            flag = check_existans_and_permisisons(environ, command[0], env_vars, flag_);
            if(flag == -1)
            {
                gc_malloc(0,0);
                exit(*((*env_vars)->status));
            }
            if(flag != -1 )
            {
                // execve(potential_paths[flag], command, NULL);
                if(!execve(potential_paths[flag], command, envp_))
                {
                    gc_malloc(0,0);
                    exit(*((*env_vars)->status));
                }
            }
        }
    }
    return;
}

