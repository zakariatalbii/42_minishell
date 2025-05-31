/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:14:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/31 10:50:39 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void pipe_line(t_tree *tree, char **PWD, char **OLDPWD)
{
    int fd[2];
    int pid[2];
    
    pipe(fd);
    pid[0] = fork();
    if (pid[0] == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        recursion(tree->data.pipe.rtree, PWD,OLDPWD);
        close(fd[1]);
    }
    pid[1] = fork();
    if (pid[1] == 0) 
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        recursion(tree->data.pipe.ltree, PWD,OLDPWD);
        close(fd[0]);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
}
void recursion(t_tree *tree, char **PWD, char **OLDPWD)
{
   
    int pid;
    static int flag;
    
    if (!tree) 
        return;
    if (tree->type == 0) 
    {
        if(flag == 0)
        {
            pid =fork();
            if(pid == 0)
                execution_entery(tree->data.argv, PWD, OLDPWD);
            waitpid(pid,NULL,0);
        }
        else
            execution_entery(tree->data.argv, PWD, OLDPWD);
    }
    else if (tree->type == 1)
    {
        flag = 1;
        pipe_line(tree, PWD, OLDPWD);
    } 
}
