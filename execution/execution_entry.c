/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/24 20:05:40 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


int  is_built_in(char **command)
{
    if(command)
    {
        if(!command[0])
            return(0);
        if((!ft_strcmp(command[0], "echo")) || 
            (!ft_strcmp(command[0], "cd")) || (!ft_strcmp(command[0], "pwd")) ||
                (!ft_strcmp(command[0], "export")) || (!ft_strcmp(command[0], "unset") 
                    || (!ft_strcmp(command[0], "env")) || (!ft_strcmp(command[0], "exit"))))
            return (1);
        else
            return (0);       
    }
    else
        return(0);
        
}

void execute_the_builtin(t_tree *tree, t_environ **s_environ, t_env_var **env_vars)
{
    char    **command = tree->data.argv;
    
    if(!ft_strcmp(command[0], "echo"))
        echo_execution(command, env_vars);
    else if(!ft_strcmp(command[0], "cd"))
        cd_execution(command,s_environ, env_vars);
    else if(!ft_strcmp(command[0], "pwd"))
        pwd_execution(command,env_vars);
    else if(!ft_strcmp(command[0], "export"))
        export_execution(command, s_environ, env_vars);
    else if(!ft_strcmp(command[0], "env"))
        executing_env(s_environ, env_vars);
    else if(!ft_strcmp(command[0], "unset"))
        unset_executing(command, s_environ, env_vars);
    else if(!ft_strcmp(command[0], "exit"))
    {
        exit_execution(tree, env_vars);
    }  
}

void no_pipe_execution(t_tree *tree, t_environ *environ, t_env_var **env_vars)
{
    char **command = tree->data.argv;
    int built_in;
    
    built_in = 0;
    if(!command)
        return;
    built_in = is_built_in(command);
    if(built_in == 1)
        execute_the_builtin(tree, &environ, env_vars);
    else
        external_commands_execution(command, &environ, env_vars);
        
}
