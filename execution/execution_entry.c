/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:04 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/28 22:20:12 by wnid-hsa         ###   ########.fr       */
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


 static int  is_built_in(char **command)
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

static void execute_the_builtin(char **command, char **PWD, t_environ **s_environ, char **OLDPWD)
{
    
    if(!ft_strcmp(command[0], "echo"))
        echo_execution(command);
    else if(!ft_strcmp(command[0], "cd"))
    {
        cd_execution(command, PWD,s_environ, OLDPWD);
    }
    else if(!ft_strcmp(command[0], "pwd"))
        pwd_execution(command,PWD);
    else if(!ft_strcmp(command[0], "export"))
        export_execution(command, s_environ);
    else if(!ft_strcmp(command[0], "env"))
        executing_env(s_environ);
    else if(!ft_strcmp(command[0], "unset"))
        unset_executing(command, s_environ);
    else if(!ft_strcmp(command[0], "exit"))
    {
        printf("execute exit");
        // exit_executing("exit");
    }  
}
static void execution_entery(char **command, char **PWD, char **OLDPWD)
{
    
    int built_in;
    static t_environ *environ;

    if(!environ)
        environ = making_the_environ_struct();
    built_in = 0;
    if(!command)
        return;
    built_in = is_built_in(command);
    if(built_in == 1)
        execute_the_builtin(command, PWD,&environ,OLDPWD);
    else
        printf("==> print with childy <==\n");
}

void recursion(t_tree *tree, char **PWD, char **OLDPWD)
{
    int i;

    i = 0;
    if(!tree)
        return;
    if(tree->type == 0)
       execution_entery(tree->data.argv,PWD, OLDPWD);
    else
    {
        recursion(tree->data.pipe.rtree, PWD, OLDPWD);
        recursion(tree->data.pipe.ltree, PWD, OLDPWD);
    }
}
