/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:14:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/04 16:55:20 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void error_handling(int return_value,char *failed_function)
{
    if(return_value==-1)
    {
        if(!strcmp(failed_function, "close"))
            perror("close failed\n");
        if(!strcmp(failed_function, "dup2"))
            perror("dup2 failed\n");
        if(!strcmp(failed_function, "fork"))
            perror("fork failed\n");
        if(!strcmp(failed_function, "dup"))
            perror("dup failed\n");
        if(!strcmp(failed_function, "open"))
            perror("open failed\n");
        exit(1);
    }
} 
static void pipe_line(t_tree *tree, char **PWD, char **OLDPWD)
{
    int fd[2];
    int pid[2];
    
    (1 && pipe(fd), (pid[0] = fork()), error_handling(pid[0], "fork"));
    if (pid[0] == 0)
    {
        error_handling(close(fd[0]), "close");
        error_handling(dup2(fd[1], STDOUT_FILENO), "dup2");
        recursion(tree->data.pipe.rtree, PWD,OLDPWD);
        error_handling(close(fd[1]), "close");
        exit(0);
    }
    (1 && (pid[1] = fork()), error_handling(pid[1], "fork"));
    if (pid[1] == 0) 
    {
        error_handling(close(fd[1]), "close");
        error_handling(dup2(fd[0], STDIN_FILENO), "dup2");
        recursion(tree->data.pipe.ltree, PWD,OLDPWD);
        error_handling(close(fd[0]), "close");
        exit(0);
    }
    error_handling(close(fd[0]), "close");
    error_handling(close(fd[1]), "close");
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
}

static void command_execution(t_tree *tree, int flag, char **PWD, char **OLDPWD)
{
    
    int pid;
    
    if(flag == 0)
    {
        pid =fork();
        error_handling(pid, "close");
        if(pid == 0)
        {
            execution_entery(tree->data.argv, PWD, OLDPWD);
            exit(0);
        }
        waitpid(pid,NULL,0);
    }
    else
    {
        execution_entery(tree->data.argv, PWD, OLDPWD);
        exit(0);
    }
}

void recursion(t_tree *tree, char **PWD, char **OLDPWD)
{   
    static int flag;

    if (!tree) 
        return;
    if (tree->type == 0) 
        command_execution(tree, flag, PWD,OLDPWD);
    else if (tree->type == 1)
    {
        flag = 1;
        pipe_line(tree, PWD, OLDPWD);
        flag = 0;
    }
    else if (tree->type == 2)
        infile_handling(tree, PWD, OLDPWD);
    else if (tree->type == 3)
        outfile_handling(tree, PWD, OLDPWD);
    else if (tree->type == 4)
        heredoc_handling(tree, PWD, OLDPWD);
    else if(tree->type == 5)
        append_handling(tree, PWD, OLDPWD);
}
